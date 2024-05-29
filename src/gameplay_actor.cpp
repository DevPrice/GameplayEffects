#include "gameplay_actor.h"
#include "binding_macros.h"
#include "containers.h"
#include "effects/effect_execution.h"
#include "effects/time_source.h"
#include "modifiers/modifier_aggregator.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <memory>

using namespace godot;

void ActiveEffectHandle::_bind_methods() {
}

std::unique_ptr<ActiveEffect> ActiveEffectHandle::get_active_effect() const {
    if (active_effect) {
        return std::make_unique<ActiveEffect>(*active_effect);
    }
    return nullptr;
}
void ActiveEffectHandle::set_active_effect(const ActiveEffect& p_active_effect) {
    active_effect = std::make_unique<ActiveEffect>(p_active_effect);
}

void GameplayActor::_bind_methods() {
    ADD_SIGNAL(MethodInfo("stat_changed",
        PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "GameplayStat"),
        PropertyInfo(Variant::FLOAT, "new_value"),
        PropertyInfo(Variant::FLOAT, "old_value")));
    ADD_SIGNAL(MethodInfo("receiving_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    ADD_SIGNAL(MethodInfo("received_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
    BIND_STATIC_METHOD(GameplayActor, find_actor_for_node, "node")
    BIND_METHOD(GameplayActor, get_stat_base_value, "stat")
    BIND_METHOD(GameplayActor, get_stat_current_value, "stat")
    BIND_METHOD(GameplayActor, make_effect_spec, "effect")
    BIND_METHOD(GameplayActor, apply_effect_to_self, "effect")
    BIND_METHOD(GameplayActor, apply_effect_to_target, "effect", "target")
    BIND_METHOD(GameplayActor, apply_effect_spec, "spec")
    BIND_VIRTUAL_METHOD(GameplayActor, _make_effect_context)
}

StatSnapshot GameplayActor::get_stat_snapshot(const Ref<GameplayStat>& stat) const {
    if (!stat_values.has(stat)) {
        UtilityFunctions::push_warning("Attempted to get snapshot of missing stat: ", stat->get_name());
        StatSnapshot snapshot;
        return snapshot;
    }
    return stat_values.get(stat);
}

float GameplayActor::get_stat_base_value(Ref<GameplayStat> stat) const {
    return get_stat_snapshot(stat).base_value;
}

float GameplayActor::get_stat_current_value(Ref<GameplayStat> stat) const {
    return get_stat_snapshot(stat).current_value;
}

Ref<GameplayEffectSpec> GameplayActor::make_effect_spec(Ref<GameplayEffect> effect) {
    Ref<GameplayEffectSpec> spec = memnew(GameplayEffectSpec);
    spec->set_effect(effect);
    spec->set_context(_make_effect_context());
    return spec;
}

Ref<GameplayEffectContext> GameplayActor::_make_effect_context() {
    Ref<GameplayEffectContext> effect_context = memnew(GameplayEffectContext);
    effect_context->set_source_actor(this);
    return effect_context;
}

EffectExecutionContext GameplayActor::_make_execution_context(Ref<GameplayEffectSpec>& spec) {
    return EffectExecutionContext{spec, this};
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_to_self(Ref<GameplayEffect> effect) {
    return apply_effect_to_target(effect, this);
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_to_target(Ref<GameplayEffect> effect, Node* target) {
    if (GameplayActor* target_actor = find_actor_for_node(target)) {
        return target_actor->apply_effect_spec(make_effect_spec(effect));
    }
    return nullptr;
}

Ref<ActiveEffectHandle> GameplayActor::apply_effect_spec(Ref<GameplayEffectSpec> spec) {
    if (!spec.is_valid()) return nullptr;

    const Ref<GameplayEffect> effect = spec->get_effect();
    const EffectExecutionContext execution_context = _make_execution_context(spec);
    const Ref<EffectLifetime> lifetime = effect->get_lifetime();

    const TypedArray<GameplayRequirements> application_requirements = spec->get_effect()->get_application_requirements();
    const bool requirements_met = array_all_of(application_requirements, [&execution_context](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || requirements->requirements_met(execution_context);
    });
    if (!requirements_met) return nullptr;

    emit_signal("receiving_effect", spec);

    const ActiveEffect active_effect = ActiveEffect{execution_context};

    if (lifetime.is_null() || lifetime->get_execute_on_application()) {
        _execute_effect(active_effect);
    } else {
        active_effects[active_effect] = active_effect.capture_modifier_snapshot();
        _recalculate_stats(stat_values);
    }

    emit_signal("received_effect", spec);

    Ref<ActiveEffectHandle> handle = memnew(ActiveEffectHandle);
    handle->set_active_effect(active_effect);

    if (lifetime.is_valid()) {
        Ref<ModifierMagnitude> period = lifetime->get_period();
        Ref<TimeSource> time_source = lifetime->get_time_source();
        if (period.is_valid() && time_source.is_valid()) {
            float period_magnitude = period->get_magnitude(execution_context);
            Ref<EffectTimer> period_timer = lifetime->get_time_source()->create_interval(execution_context, period_magnitude);
            period_timer->set_callback([this, &active_effect]() {
                _execute_effect(active_effect);
            });
            active_periods[active_effect] = period_timer;
        }
        Ref<ModifierMagnitude> duration = lifetime->get_duration();
        if (duration.is_valid()) {
            float duration_magnitude = duration->get_magnitude(execution_context);
            if (duration_magnitude > 0 && time_source.is_valid()) {
                Ref<EffectTimer> timer = lifetime->get_time_source()->create_timer(execution_context, duration_magnitude);
                timer->set_callback([this, &active_effect]() {
                    _remove_effect(active_effect);
                });
            } else {
                _remove_effect(active_effect);
            }
        }
    }

    return handle;
}

void GameplayActor::_execute_effect(const ActiveEffect& active_effect) {
    const EffectExecutionContext execution_context = active_effect.execution_context;
    const Ref<GameplayEffect> effect = execution_context.spec->get_effect();

    const Ref<EffectLifetime> lifetime = effect->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [&execution_context](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(execution_context);
        });
        if (!requirements_met) return;
    }

    TypedArray<StatModifier> modifiers = effect->get_modifiers();
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifier_snapshot = active_effect.capture_modifier_snapshot();

    ModifierAggregator base_aggregator;
    if (effect->is_instant()) {
        base_aggregator.modifiers.insert(base_aggregator.modifiers.end(), modifier_snapshot.begin(), modifier_snapshot.end());
    } else {
        active_effects[active_effect] = modifier_snapshot;
    }

    HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;

    TypedArray<EffectExecution> executions = effect->get_executions();
    Ref<EffectExecutionOutput> execution_output = memnew(EffectExecutionOutput);
    for (int i = 0; i < executions.size(); i++) {
        const Ref<EffectExecution> execution = executions[i];
        if (execution.is_valid()) {
            execution->execute(execution_context, execution_output);
        }
    }

    std::vector<std::shared_ptr<IEvaluatedModifier>> execution_modifiers = execution_output->get_modifiers();
    base_aggregator.modifiers.insert(base_aggregator.modifiers.end(), execution_modifiers.begin(), execution_modifiers.end());

    for (auto& stat_value : stat_snapshot) {
        float modified_value = 0.f;
        if (base_aggregator.get_modified_value(stat_value.key, stat_value.value.base_value, modified_value)) {
            StatSnapshot new_snapshot{modified_value, stat_value.value.current_value};
            stat_values[stat_value.key] = new_snapshot;
        }
    }

    _recalculate_stats(stat_snapshot);
}

void GameplayActor::_recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot) {
    std::vector<Ref<GameplayStat>> modified_stats;
    ModifierAggregator aggregator;
    for (auto& effect_modifiers : active_effects) {
        aggregator.modifiers.insert(aggregator.modifiers.begin(), effect_modifiers.second.begin(), effect_modifiers.second.end());
    }
    for (auto& stat : stat_values) {
        float initial_value = stat.value.current_value;
        float modified_value = aggregator.get_modified_value(stat.key, stat.value.base_value);
        stat_values[stat.key] = StatSnapshot{stat.value.base_value, modified_value};
        if (abs(modified_value - initial_value) > 1e-5) {
            modified_stats.push_back(stat.key);
        }
    }
    for (Ref<GameplayStat> stat : modified_stats) {
        emit_signal("stat_changed", stat, stat_values.get(stat).current_value, stat_snapshot.get(stat).current_value);
    }
}

bool GameplayActor::remove_effect(Ref<ActiveEffectHandle> handle) {
    if (handle.is_valid()) {
        if (std::unique_ptr<ActiveEffect> effect_ref = handle->get_active_effect()) {
            return _remove_effect(*effect_ref);
        }
    }
    return false;
}

bool GameplayActor::_remove_effect(const ActiveEffect& active_effect) {
    if (active_periods.count(active_effect)) {
        active_periods[active_effect]->stop();
        active_periods.erase(active_effect);
    }
    bool removed = active_effects.erase(active_effect);
    _recalculate_stats(stat_values);
    return removed;
}

GameplayActor* GameplayActor::find_actor_for_node(Node* node) {
    GameplayActor* as_actor = Object::cast_to<GameplayActor>(node);
    if (as_actor) return as_actor;
    // TODO: Handle avatar
    return nullptr;
}

TypedArray<GameplayStat> GameplayActor::get_stats() const {
    return stats;
}

void GameplayActor::set_stats(const TypedArray<GameplayStat> p_stats) {
    stats = p_stats;
    for (int i = 0; i < stats.size(); i++) {
        const Ref<GameplayStat> stat = stats[i];
        const StatSnapshot snapshot{stat->get_base_value(), stat->get_base_value()};
        if (!stat_values.has(stat)) {
            stat_values[stat] = snapshot;
        }
    }
    for (auto it = stat_values.begin(); it != stat_values.end(); ++it) {
        if (!p_stats.has(it->key)) {
            stat_values.remove(it);
        }
    }
}

std::vector<std::shared_ptr<IEvaluatedModifier>> ActiveEffect::capture_modifier_snapshot() const {
    const TypedArray<StatModifier> modifiers = execution_context.spec->get_effect()->get_modifiers();
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifier_snapshot;
    for (size_t i = 0; i < modifiers.size(); i++) {
        const Ref<StatModifier> modifier = modifiers[i];
        const float magnitude = modifier->get_magnitude()->get_magnitude(execution_context);
        std::shared_ptr<IEvaluatedModifier> evaluated_modifier = std::make_shared<ModifierSnapshot>(modifier, execution_context, magnitude);
        modifier_snapshot.push_back(evaluated_modifier);
    }
    return modifier_snapshot;
}
