#include "gameplay_actor.h"
#include "binding_macros.h"
#include "containers.h"
#include "weak_object_ref.h"
#include "effects/effect_execution.h"
#include "effects/grant_tags_component.h"
#include "effects/time_source.h"
#include "modifiers/modifier_aggregator.h"
#include "modifiers/modifier_snapshot.h"
#include "stats/captured_stat_evaluator.h"
#include "stats/stat_evaluator.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <memory>

using namespace godot;

void ActiveEffectHandle::_bind_methods() {
    BIND_METHOD(ActiveEffectHandle, get_spec)
}

void StatSignals::_bind_methods() {
    ADD_SIGNAL(MethodInfo("base_value_changed",
        PropertyInfo(Variant::FLOAT, "new_value"),
        PropertyInfo(Variant::FLOAT, "old_value")));
    ADD_SIGNAL(MethodInfo("current_value_changed",
        PropertyInfo(Variant::FLOAT, "new_value"),
        PropertyInfo(Variant::FLOAT, "old_value")));
}

void GameplayActor::_bind_methods() {
    ADD_SIGNAL(MethodInfo("stat_changed",
        PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "GameplayStat"),
        PropertyInfo(Variant::FLOAT, "new_value"),
        PropertyInfo(Variant::FLOAT, "old_value")));
    ADD_SIGNAL(MethodInfo("tags_changed",
        PropertyInfo(Variant::PACKED_STRING_ARRAY, "added_tags"),
        PropertyInfo(Variant::PACKED_STRING_ARRAY, "removed_tags")));
    ADD_SIGNAL(MethodInfo("avatar_changed", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_NODE_TYPE, "Node")));
    ADD_SIGNAL(MethodInfo("receiving_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    ADD_SIGNAL(MethodInfo("received_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
    BIND_GET_SET_NODE(GameplayActor, avatar, Node)
    BIND_GET_SET(GameplayActor, replicated_tags, GDEXTENSION_VARIANT_TYPE_PACKED_STRING_ARRAY, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NONE)
    BIND_STATIC_METHOD(GameplayActor, find_actor_for_node, "node")
    BIND_METHOD(GameplayActor, get_loose_tags)
    BIND_METHOD(GameplayActor, get_granted_tags)
    BIND_METHOD(GameplayActor, has_tag, "tag")
    BIND_METHOD(GameplayActor, has_tag_exact, "tag")
    BIND_METHOD(GameplayActor, get_stat_base_value, "stat")
    BIND_METHOD(GameplayActor, get_stat_current_value, "stat")
    BIND_METHOD(GameplayActor, base_value_changed, "stat")
    BIND_METHOD(GameplayActor, current_value_changed, "stat")
    BIND_METHOD(GameplayActor, apply_effect_spec, "spec")
    BIND_METHOD(GameplayActor, remove_effect, "handle")
    BIND_METHOD(GameplayActor, _make_effect_context)
    BIND_METHOD(GameplayActor, _on_loose_tags_changed)
    GDVIRTUAL_BIND(_get_custom_context_data)

    const Dictionary default_tag_magnitudes;
    ClassDB::bind_method(D_METHOD("can_apply_effect", "effect", "tag_magnitudes"), &GameplayActor::can_apply_effect, DEFVAL(default_tag_magnitudes));
    ClassDB::bind_method(D_METHOD("can_apply_effect_spec", "spec"), &GameplayActor::can_apply_effect_spec);
    ClassDB::bind_method(D_METHOD("can_afford_effect", "effect", "tag_magnitudes"), &GameplayActor::can_afford_effect, DEFVAL(default_tag_magnitudes));
    ClassDB::bind_method(D_METHOD("can_afford_effect_spec", "spec"), &GameplayActor::can_afford_effect_spec);
    ClassDB::bind_method(D_METHOD("make_effect_spec", "effect", "tag_magnitudes"), &GameplayActor::make_effect_spec, DEFVAL(default_tag_magnitudes));
    ClassDB::bind_method(D_METHOD("apply_effect_to_self", "effect", "tag_magnitudes"), &GameplayActor::apply_effect_to_self, DEFVAL(default_tag_magnitudes));
    ClassDB::bind_method(D_METHOD("apply_effect_to_target", "effect", "target", "tag_magnitudes"), &GameplayActor::apply_effect_to_target, DEFVAL(default_tag_magnitudes));
}

std::shared_ptr<ActiveEffect> ActiveEffectHandle::get_active_effect() const {
    return active_effect;
}

void ActiveEffectHandle::set_active_effect(const ActiveEffect& p_active_effect) {
    active_effect = std::make_shared<ActiveEffect>(p_active_effect);
}

Ref<GameplayEffectSpec> ActiveEffectHandle::get_spec() const {
    if (active_effect) {
        const Ref<EffectApplicationContext> application_context = active_effect->application_context;
        if (application_context.is_valid()) {
            return application_context->get_spec();
        }
    }
    return nullptr;
}

Ref<GameplayTagContainer> GameplayActor::get_loose_tags() {
    if (loose_tags.is_null()) {
        loose_tags.instantiate();
        loose_tags->connect("tags_changed", callable_mp(this, &GameplayActor::_on_loose_tags_changed));
    }
    return loose_tags;
}

PackedStringArray GameplayActor::get_granted_tags() const {
    PackedStringArray result;
    granted_tags.to_string_array(result);
    if (!is_multiplayer_authority()) {
        replicated_tags.to_string_array(result);
    }
    return result;
}

bool GameplayActor::has_tag(const String& tag) const {
    if (!is_multiplayer_authority()) {
        return replicated_tags.has_tag(tag);
    }
    return (loose_tags.is_valid() && loose_tags->has_tag(tag)) || granted_tags.has_tag(tag);
}

bool GameplayActor::has_tag_exact(const String& tag) const {
    if (!is_multiplayer_authority()) {
        return replicated_tags.has_tag_exact(tag);
    }
    return (loose_tags.is_valid() && loose_tags->has_tag_exact(tag)) || granted_tags.has_tag_exact(tag);
}

StatSnapshot GameplayActor::get_stat_snapshot(const Ref<GameplayStat>& stat) const {
    if (!stat_values.has(stat)) {
        UtilityFunctions::push_warning("Attempted to get snapshot of missing stat: ", stat->get_name());
        return StatSnapshot();
    }
    return stat_values.get(stat);
}

stat_value_t GameplayActor::get_stat_base_value(const Ref<GameplayStat>& stat) const {
    return get_stat_snapshot(stat).base_value;
}

stat_value_t GameplayActor::get_stat_current_value(const Ref<GameplayStat>& stat) const {
    return get_stat_snapshot(stat).current_value;
}

void GameplayActor::set_stat_base_value(const Ref<GameplayStat>& stat, const stat_value_t base_value) {
    const HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;
    stat_values[stat].base_value = base_value;
    _recalculate_stats(stat_snapshot);
}

Signal GameplayActor::base_value_changed(const Ref<GameplayStat>& stat) {
    return _get_stat_signal(stat, "base_value_changed");
}

Signal GameplayActor::current_value_changed(const Ref<GameplayStat>& stat) {
    return _get_stat_signal(stat, "current_value_changed");
}

Signal GameplayActor::_get_stat_signal(const Ref<GameplayStat>& stat, const StringName& signal_name) {
    const auto element = stat_signals.find(stat);
    if (element != stat_signals.end()) {
        const Ref<StatSignals> signals = element->second;
        if (signals.is_valid()) {
            return Signal(signals.ptr(), signal_name);
        }
    }
    Ref<StatSignals> new_signals;
    new_signals.instantiate();
    stat_signals.emplace(stat, new_signals);
    return Signal(new_signals.ptr(), signal_name);
}

void GameplayActor::_on_loose_tags_changed(const PackedStringArray& added_tags, const PackedStringArray& removed_tags) {
    PackedStringArray actual_added_tags;
    PackedStringArray actual_removed_tags;
    for (size_t i = 0; i < added_tags.size(); ++i) {
        const String tag_string = added_tags[i];
        const GameplayTag tag(tag_string);
        if (!granted_tags.has_tag_exact(tag)) {
            actual_added_tags.append(tag_string);
        }
    }
    for (size_t i = 0; i < removed_tags.size(); ++i) {
        const String tag_string = removed_tags[i];
        const GameplayTag tag(tag_string);
        if (!granted_tags.has_tag_exact(tag)) {
            actual_removed_tags.append(tag_string);
        }
    }
    if (!actual_added_tags.is_empty() || !removed_tags.is_empty()) {
        _recalculate_stats();
        emit_signal("tags_changed", actual_added_tags, actual_removed_tags);
    }
}

ActorSnapshot GameplayActor::capture_snapshot() const {
    const HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;
    std::vector<std::shared_ptr<EvaluatedModifier>> modifier_snapshot;

    for (auto& [_, effect_state] : active_effects) {
        modifier_snapshot.insert(modifier_snapshot.end(), effect_state.modifiers.begin(), effect_state.modifiers.end());
    }

    return ActorSnapshot{stat_snapshot, modifier_snapshot};
}

Ref<GameplayEffectSpec> GameplayActor::make_effect_spec(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes) {
    Ref<GameplayEffectSpec> spec;
    spec.instantiate();
    spec->set_effect(effect);
    spec->set_context(_make_effect_context());
    spec->add_tag_magnitudes(tag_magnitudes);
    return spec;
}

bool GameplayActor::can_apply_effect(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes) {
    const Ref<GameplayEffectSpec> spec = make_effect_spec(effect, tag_magnitudes);
    return can_apply_effect_spec(spec);
}

bool GameplayActor::can_apply_effect_spec(const Ref<GameplayEffectSpec>& spec) {
    if (spec.is_null()) return false;

    const Ref<GameplayEffect> effect = spec->get_effect();
    const Ref<EffectApplicationContext> application_context = _make_application_context(spec);

    const TypedArray<GameplayRequirements> application_requirements = spec->get_effect()->get_application_requirements();
    return array_all_of(application_requirements, [&application_context](Ref<GameplayRequirements> requirements) {
        return requirements.is_null() || requirements->requirements_met(application_context);
    });
}

bool GameplayActor::can_afford_effect(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes) {
    const Ref<GameplayEffectSpec> spec = make_effect_spec(effect, tag_magnitudes);
    return can_afford_effect_spec(spec);
}

bool GameplayActor::can_afford_effect_spec(const Ref<GameplayEffectSpec>& spec) {
    if (spec.is_null()) return true;

    const Ref<GameplayEffect> effect = spec->get_effect();
    const Ref<EffectApplicationContext> application_context = _make_application_context(spec);
    const ActiveEffect active_effect = ActiveEffect(application_context);

    TypedArray<StatModifier> modifiers = effect->get_modifiers();
    const std::vector<std::shared_ptr<EvaluatedModifier>> modifier_snapshot = active_effect.capture_modifier_snapshot();

    const ModifierAggregator aggregator(modifier_snapshot);
    for (auto [stat, stat_snapshot] : stat_values) {
        const stat_value_t modified_value = aggregator.get_modified_value(stat, stat_snapshot.base_value);
        if (modified_value < stat_value_t{}) {
            return false;
        }
    }
    return true;
}

Ref<GameplayEffectContext> GameplayActor::_make_effect_context() {
    Ref<GameplayEffectContext> effect_context;
    effect_context.instantiate();
    effect_context->set_source_actor(this);
    effect_context->set_source_snapshot(capture_snapshot());

    Variant custom_data;
    if (GDVIRTUAL_CALL(_get_custom_context_data, custom_data)) {
        effect_context->set_custom_data(custom_data);
    }

    return effect_context;
}

Ref<EffectApplicationContext> GameplayActor::_make_application_context(const Ref<GameplayEffectSpec>& spec) {
    Ref<EffectApplicationContext> application_context;
    application_context.instantiate();
    application_context->set_spec(spec);
    application_context->set_target_actor(this);
    application_context->set_target_snapshot(capture_snapshot());
    return application_context;
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_to_self(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes) {
    return apply_effect_to_target(effect, this, tag_magnitudes);
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_to_target(const Ref<GameplayEffect>& effect, Node* target, const Dictionary& tag_magnitudes) {
    if (GameplayActor* target_actor = find_actor_for_node(target)) {
        return target_actor->apply_effect_spec(make_effect_spec(effect, tag_magnitudes));
    }
    return nullptr;
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_spec(const Ref<GameplayEffectSpec>& spec) {
    if (!spec.is_valid()) return nullptr;

    const Ref<GameplayEffect> effect = spec->get_effect();
    const Ref<EffectApplicationContext> application_context = _make_application_context(spec);
    const Ref<EffectLifetime> lifetime = effect->get_lifetime();

    const TypedArray<GameplayRequirements> application_requirements = spec->get_effect()->get_application_requirements();
    const bool requirements_met = array_all_of(application_requirements, [&application_context](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || requirements->requirements_met(application_context);
    });
    if (!requirements_met) return nullptr;

    emit_signal("receiving_effect", spec);

    TypedArray<EffectComponent> effect_components = effect->get_components();
    for (int i = 0; i < effect_components.size(); ++i) {
        Ref<EffectComponent> effect_component = effect_components[i];
        if (effect_component.is_valid()) {
            effect_component->on_application(application_context);
        }
    }

    const ActiveEffect active_effect = ActiveEffect{application_context};

    if (lifetime.is_null() || lifetime->get_execute_on_application()) {
        _execute_effect(active_effect);
    } else {
        active_effects[active_effect].granted_tags = active_effect.capture_granted_tags();
        active_effects[active_effect].modifiers = active_effect.capture_modifier_snapshot();
        _recalculate_stats();
    }

    emit_signal("received_effect", spec);

    Ref<ActiveEffectHandle> handle;
    handle.instantiate();
    handle->set_active_effect(active_effect);

    if (lifetime.is_valid()) {
        const Ref<TimeSource> time_source = lifetime->get_time_source();
        if (time_source.is_valid()) {
            const Ref<ModifierMagnitude> period = lifetime->get_period();
            WeakObjectRef<GameplayActor> weak_this(this);
            if (period.is_valid()) {
                const stat_value_t period_magnitude = period->get_magnitude(application_context);
                const Ref<EffectTimer> period_timer = time_source->create_interval(application_context, period_magnitude);
                period_timer->set_callback([weak_this, active_effect] {
                    if (weak_this) {
                        weak_this->_execute_effect(active_effect);
                    }
                });
                active_effects[active_effect].period = period_timer;
            }
            const Ref<ModifierMagnitude> duration = lifetime->get_duration();
            if (duration.is_valid()) {
                const stat_value_t duration_magnitude = duration->get_magnitude(application_context);
                if (duration_magnitude > 0) {
                    const Ref<EffectTimer> duration_timer = time_source->create_timer(application_context, duration_magnitude);
                    duration_timer->set_callback([weak_this, active_effect] {
                        if (weak_this) {
                            weak_this->_remove_effect(active_effect);
                        }
                    });
                    active_effects[active_effect].duration = duration_timer;
                } else {
                    _remove_effect(active_effect);
                }
            }
        }
    }

    return handle;
}

void GameplayActor::_execute_effect(const ActiveEffect& active_effect) {
    const Ref<EffectApplicationContext> application_context = active_effect.application_context;
    if (application_context.is_null()) {
        UtilityFunctions::push_error("Attempted to execute effect with no execution context!");
        return;
    }
    const Ref<GameplayEffectSpec> spec = application_context->get_spec();
    if (spec.is_null()) {
        UtilityFunctions::push_error("Attempted to execute effect with no spec!");
        return;
    }
    const Ref<GameplayEffect> effect = spec->get_effect();
    if (effect.is_null()) {
        UtilityFunctions::push_error("Attempted to execute effect with no definition!");
        return;
    }

    const Ref<EffectLifetime> lifetime = effect->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [&application_context](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(application_context);
        });
        if (!requirements_met) return;
    }

    TypedArray<StatModifier> modifiers = effect->get_modifiers();
    const std::vector<std::shared_ptr<EvaluatedModifier>> modifier_snapshot = active_effect.capture_modifier_snapshot();

    ModifierAggregator base_aggregator;
    if (effect->is_instant()) {
        base_aggregator.add_modifiers(modifier_snapshot);
    } else {
        active_effects[active_effect].granted_tags = active_effect.capture_granted_tags();
        active_effects[active_effect].modifiers = modifier_snapshot;
    }

    TypedArray<EffectExecution> executions = effect->get_executions();
    Ref<EffectExecutionOutput> execution_output;
    execution_output.instantiate();

    if (executions.size() > 0) {
        const std::unique_ptr<CapturedStatEvaluator> captured_stat_evaluator = std::make_unique<CapturedStatEvaluator>(application_context);
        Ref<StatEvaluator> stat_evaluator;
        stat_evaluator.instantiate();
        stat_evaluator->set_evaluator(captured_stat_evaluator.get());
        for (int i = 0; i < executions.size(); i++) {
            const Ref<EffectExecution> execution = executions[i];
            if (execution.is_valid()) {
                execution->execute(application_context, stat_evaluator, execution_output);
            }
        }
        stat_evaluator->set_evaluator(nullptr);
    }

    HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;

    const std::vector<std::shared_ptr<EvaluatedModifier>> execution_modifiers = execution_output->get_modifiers();
    base_aggregator.add_modifiers(execution_modifiers);

    for (auto& stat_value : stat_snapshot) {
        stat_value_t modified_value{};
        if (base_aggregator.get_modified_value(stat_value.key, stat_value.value.base_value, modified_value)) {
            const StatSnapshot new_snapshot{ modified_value, stat_value.value.current_value };
            stat_values[stat_value.key] = new_snapshot;
        }
    }

    _recalculate_stats(stat_snapshot);
}

void GameplayActor::_recalculate_stats() {
    const HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;
    _recalculate_stats(stat_snapshot);
}

void GameplayActor::_recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot) {
    ModifierAggregator aggregator;
    GameplayTagSet initial_granted_tags(granted_tags);
    granted_tags.clear();
    for (auto& [_, effect_state] : active_effects) {
        const std::vector<std::shared_ptr<EvaluatedModifier>>& effect_modifiers = effect_state.modifiers;
        aggregator.add_modifiers(effect_modifiers);
        granted_tags += effect_state.granted_tags;
    }
    for (auto& stat : stat_values) {
        stat_value_t base_value = stat.value.base_value;

        for (auto& [active_effect, _] : active_effects) {
            Ref<EffectApplicationContext> application_context = active_effect.application_context;
            if (application_context.is_valid()) {
                Ref<GameplayEffectSpec> spec = application_context->get_spec();
                if (spec.is_valid()) {
                    TypedArray<EffectComponent> effect_components = spec->get_effect()->get_components();
                    for (int i = 0; i < effect_components.size(); ++i) {
                        const Ref<EffectComponent>& effect_component = effect_components[i];
                        if (effect_component.is_valid()) {
                            effect_component->on_base_value_changing(application_context, stat.key, base_value);
                        }
                    }
                    for (int i = 0; i < effect_components.size(); ++i) {
                        const Ref<EffectComponent>& effect_component = effect_components[i];
                        if (effect_component.is_valid()) {
                            effect_component->on_base_value_changed(application_context, stat.key, base_value);
                        }
                    }
                }
            }
        }

        stat_value_t modified_value = aggregator.get_modified_value(stat.key, base_value);

        for (const auto& [active_effect, _] : active_effects) {
            Ref<EffectApplicationContext> application_context = active_effect.application_context;
            if (application_context.is_valid()) {
                Ref<GameplayEffectSpec> spec = application_context->get_spec();
                if (spec.is_valid()) {
                    TypedArray<EffectComponent> effect_components = spec->get_effect()->get_components();
                    for (int i = 0; i < effect_components.size(); ++i) {
                        const Ref<EffectComponent>& effect_component = effect_components[i];
                        if (effect_component.is_valid()) {
                            effect_component->on_current_value_changing(application_context, stat.key, modified_value);
                        }
                    }
                }
            }
        }

        stat_values[stat.key] = StatSnapshot{base_value, modified_value};

        for (const auto& [active_effect, _] : active_effects) {
            Ref<EffectApplicationContext> application_context = active_effect.application_context;
            if (application_context.is_valid()) {
                Ref<GameplayEffectSpec> spec = application_context->get_spec();
                if (spec.is_valid()) {
                    TypedArray<EffectComponent> effect_components = spec->get_effect()->get_components();
                    for (int i = 0; i < effect_components.size(); ++i) {
                        const Ref<EffectComponent>& effect_component = effect_components[i];
                        if (effect_component.is_valid()) {
                            effect_component->on_current_value_changed(application_context, stat.key, modified_value);
                        }
                    }
                }
            }
        }
    }
    for (auto& [stat, _] : stat_values) {
        const Ref<StatSignals> signals = stat_signals[stat];
        const stat_value_t initial_value = stat_snapshot.get(stat).current_value;
        const stat_value_t modified_value = stat_values.get(stat).current_value;
        const bool current_value_changed = !Math::is_equal_approx(initial_value, modified_value);
        if (signals.is_valid()) {
            const stat_value_t initial_base_value = stat_snapshot.get(stat).base_value;
            const stat_value_t modified_base_value = stat_values.get(stat).base_value;
            if (!Math::is_equal_approx(initial_base_value, modified_base_value)) {
                signals->emit_signal("base_value_changed", modified_base_value, initial_base_value);
            }
            if (current_value_changed) {
                signals->emit_signal("current_value_changed", modified_value, initial_value);
            }
        }
        if (current_value_changed) {
            emit_signal("stat_changed", stat, modified_value, initial_value);
        }
    }
    GameplayTagSet loose_tag_set = loose_tags.is_valid() ? loose_tags->to_tag_set() : GameplayTagSet();
    GameplayTagSet added = granted_tags - initial_granted_tags - loose_tag_set;
    GameplayTagSet removed = initial_granted_tags - granted_tags - loose_tag_set;
    if (!added.is_empty() || !removed.is_empty()) {
        PackedStringArray added_tags;
        added.to_string_array(added_tags);
        PackedStringArray removed_tags;
        removed.to_string_array(removed_tags);
        emit_signal("tags_changed", added_tags, removed_tags);
    }
}

bool GameplayActor::remove_effect(const Ref<ActiveEffectHandle>& handle) {
    if (handle.is_valid()) {
        if (const std::shared_ptr<ActiveEffect> effect_ref = handle->get_active_effect()) {
            return _remove_effect(*effect_ref);
        }
    }
    return false;
}

bool GameplayActor::_remove_effect(const ActiveEffect& active_effect) {
    const Ref<EffectApplicationContext> application_context = active_effect.application_context;
    const bool removed = active_effects.erase(active_effect);

    if (removed) {
        _recalculate_stats();

        if (application_context.is_valid()) {
            const Ref<GameplayEffectSpec> spec = application_context->get_spec();
            if (spec.is_valid()) {
                const Ref<GameplayEffect> effect = spec->get_effect();
                if (effect.is_valid()) {
                    const TypedArray<EffectComponent> effect_components = effect->get_components();
                    for (int i = 0; i < effect_components.size(); ++i) {
                        const Ref<EffectComponent> effect_component = effect_components[i];
                        if (effect_component.is_valid()) {
                            effect_component->on_removal(application_context);
                        }
                    }
                }
            }
        }
    }

    return removed;
}

StringName& GameplayActor::get_actor_meta_name() {
    static StringName actor_meta_name("instigator_gameplay_actor");
    return actor_meta_name;
}

GameplayActor* GameplayActor::find_actor_for_node(Node* node) {
    if (GameplayActor* as_actor = cast_to<GameplayActor>(node)) return as_actor;

    const StringName& actor_meta_name = get_actor_meta_name();
    if (node) {
        if (node->has_meta(actor_meta_name)) {
            if (GameplayActor* instigating_actor = cast_to<GameplayActor>(node->get_meta(actor_meta_name))) {
                return instigating_actor;
            }
        }
        static const StringName get_gameplay_actor_method("get_gameplay_actor");
        if (node->has_method(get_gameplay_actor_method)) {
            if (GameplayActor* actor = cast_to<GameplayActor>(node->call(get_gameplay_actor_method))) {
                return actor;
            }
        }
    }

    return nullptr;
}

void GameplayActor::set_owning_actor(Node* node, const GameplayActor* actor) {
    if (node == nullptr) return;

    if (actor) {
        node->set_meta(get_actor_meta_name(), actor);
    } else {
        node->remove_meta(get_actor_meta_name());
    }
}

TypedArray<GameplayStat> GameplayActor::get_stats() const {
    TypedArray<GameplayStat> stats;
    for (const auto& [stat, _] : stat_values) {
        stats.append(stat);
    }
    stats.make_read_only();
    return stats;
}

void GameplayActor::set_stats(const TypedArray<GameplayStat> p_stats) {
    for (int i = 0; i < p_stats.size(); i++) {
        const Ref<GameplayStat> stat = p_stats[i];
        if (stat.is_valid()) {
            if (!stat_values.has(stat)) {
                stat_values[stat] = StatSnapshot{ stat->get_base_value(), stat->get_base_value() };
            }
        }
    }
    for (auto it = stat_values.begin(); it != stat_values.end(); ++it) {
        if (!p_stats.has(it->key)) {
            stat_values.remove(it);
            stat_signals.erase(it->key);
        }
    }
}

Node* GameplayActor::get_avatar() const {
    return cast_to<Node>(ObjectDB::get_instance(avatar_id));
}

void GameplayActor::set_avatar(Node* p_avatar) {
    Node* previous_avatar = get_avatar();
    if (previous_avatar == p_avatar) return;

    avatar_id = p_avatar ? p_avatar->get_instance_id() : ObjectID();

    if (Engine::get_singleton()->is_editor_hint()) return;

    if (previous_avatar) {
        set_owning_actor(previous_avatar, nullptr);
    }
    if (p_avatar) {
        set_owning_actor(p_avatar, this);
    }
    emit_signal("avatar_changed", p_avatar);
}

PackedStringArray GameplayActor::get_replicated_tags() const {
    if (is_multiplayer_authority()) {
        PackedStringArray all_tags;
        granted_tags.to_string_array(all_tags);
        if (loose_tags.is_valid()) {
            all_tags.append_array(loose_tags->to_array());
        }
        return all_tags;
    }
    PackedStringArray replicated_tag_array;
    replicated_tags.to_string_array(replicated_tag_array);
    return replicated_tag_array;
}

void GameplayActor::set_replicated_tags(PackedStringArray p_replicated_tags) {
    if (is_multiplayer_authority()) {
        replicated_tags = GameplayTagSet(p_replicated_tags);
    } else{
        const GameplayTagSet new_tag_set(p_replicated_tags);
        const GameplayTagSet added_tags = new_tag_set - replicated_tags - granted_tags;
        const GameplayTagSet removed_tags = replicated_tags - new_tag_set - granted_tags;
        replicated_tags = new_tag_set;
        if (!added_tags.is_empty() || !removed_tags.is_empty()) {
            _recalculate_stats();
            PackedStringArray added_array;
            added_tags.to_string_array(added_array);
            PackedStringArray removed_array;
            removed_tags.to_string_array(removed_array);
            emit_signal("tags_changed", added_array, removed_array);
        }
    }
}

std::vector<std::shared_ptr<EvaluatedModifier>> ActiveEffect::capture_modifier_snapshot() const {
    std::vector<std::shared_ptr<EvaluatedModifier>> modifier_snapshot;
    const Ref<GameplayEffectSpec> spec = application_context->get_spec();
    if (spec.is_valid()) {
        const Ref<GameplayEffect> effect = spec->get_effect();
        if (effect.is_valid()) {
            const TypedArray<StatModifier> modifiers = effect->get_modifiers();
            for (size_t i = 0; i < modifiers.size(); i++) {
                const Ref<StatModifier> modifier = modifiers[i];
                if (modifier.is_valid()) {
                    const Ref<ModifierMagnitude> magnitude = modifier->get_magnitude();
                    if (magnitude.is_valid()) {
                        const float evaluated_magnitude = magnitude->get_magnitude(application_context);
                        std::shared_ptr<EvaluatedModifier> evaluated_modifier = std::make_shared<ModifierSnapshot>(modifier, application_context, evaluated_magnitude);
                        modifier_snapshot.push_back(evaluated_modifier);
                    }
                }
            }
        }
    }
    return modifier_snapshot;
}

GameplayTagSet ActiveEffect::capture_granted_tags() const {
    GameplayTagSet result;
    if (application_context.is_valid()) {
        const Ref<GameplayEffectSpec> spec = application_context->get_spec();
        if (spec.is_valid()) {
            const Ref<GameplayEffect> effect = spec->get_effect();
            if (effect.is_valid()) {
                TypedArray<EffectComponent> components = effect->get_components();
                for (int i = 0; i < components.size(); ++i) {
                    Ref<EffectComponent> component = components[i];
                    if (component.is_valid()) {
                        if (const GrantTagsComponent* grant_tags_component = Object::cast_to<GrantTagsComponent>(*component)) {
                            PackedStringArray captured_tags = grant_tags_component->get_granted_tags();
                            for (size_t j = 0; j < captured_tags.size(); ++j) {
                                const String tag = captured_tags[i];
                                result.add_tag(tag);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}
