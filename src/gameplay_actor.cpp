#include "gameplay_actor.h"
#include "binding_macros.h"
#include "containers.h"
#include "modifiers/modifier_aggregator.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <memory>

using namespace godot;

void GameplayActor::_bind_methods() {
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
    // TODO: Support override virtuals in gdscript
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

GameplayEffectContext GameplayActor::_make_effect_context() {
    return GameplayEffectContext{this};
}

EffectExecutionContext GameplayActor::_make_execution_context(Ref<GameplayEffectSpec>& spec) {
    return EffectExecutionContext{spec, this};
}

void GameplayActor::apply_effect_to_self(Ref<GameplayEffect> effect) {
    apply_effect_to_target(effect, this);
}

void GameplayActor::apply_effect_to_target(Ref<GameplayEffect> effect, Node* target) {
    GameplayActor* target_actor = find_actor_for_node(target);
    if (target_actor) {
        target_actor->apply_effect_spec(make_effect_spec(effect));
    }
}

void GameplayActor::apply_effect_spec(Ref<GameplayEffectSpec> spec) {
    if (!spec.is_valid()) return;

    const Ref<GameplayEffect> effect = spec->get_effect();
    const EffectExecutionContext execution_context = _make_execution_context(spec);

    const TypedArray<GameplayRequirements> application_requirements = spec->get_effect()->get_application_requirements();
    const bool requirements_met = array_all_of(application_requirements, [&execution_context](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || requirements->requirements_met(execution_context);
    });
    if (!requirements_met) return;

    emit_signal("receiving_effect", spec);

    // TODO: Period

    const ActiveEffect active_effect = ActiveEffect{spec, this, execution_context};

    if (effect->is_instant() || effect->get_lifetime()->get_execute_on_application()) {
        execute_effect(active_effect);
    } else {
        // TODO: Handle non-instant effects
    }

    emit_signal("received_effect", spec);

    // TODO: Duration
}

void GameplayActor::execute_effect(const ActiveEffect& active_effect) {
    const EffectExecutionContext execution_context = active_effect.execution_context;
    const Ref<GameplayEffect> effect = active_effect.spec->get_effect();

    const Ref<EffectLifetime> lifetime = execution_context.spec->get_effect()->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [&execution_context](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(execution_context);
        });
        if (!requirements_met) return;
    }

    TypedArray<StatModifier> modifiers = effect->get_modifiers();
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifier_snapshot;
    for (size_t i = 0; i < modifiers.size(); i++) {
        Ref<StatModifier> modifier = modifiers[i];
        float magnitude = modifier->get_magnitude()->get_magnitude(execution_context);
        std::shared_ptr<IEvaluatedModifier> evaluated_modifier = std::make_shared<ModifierSnapshot>(modifier, execution_context, magnitude);
        modifier_snapshot.push_back(evaluated_modifier);
    }

    ModifierAggregator base_aggregator;
    if (effect->is_instant()) {
        base_aggregator.modifiers.insert(base_aggregator.modifiers.end(), modifier_snapshot.begin(), modifier_snapshot.end());
    } else {
        // TODO
    }

    // TODO: Capture modifier snapshot
    // TODO: Run executions
    HashMap<Ref<GameplayStat>, StatSnapshot> stat_snapshot = stat_values;
    for (auto stat_value : stat_snapshot) {
        float modified_value = 0.f;
        if (base_aggregator.get_modified_value(stat_value.key, stat_value.value.base_value, modified_value)) {
            StatSnapshot new_snapshot{modified_value, stat_value.value.current_value};
            stat_values.insert(stat_value.key, new_snapshot);
        }
    }
    // TODO: Recalculate stats
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
            stat_values.insert(stat, snapshot);
        }
    }
    // TODO: Remove missing stats
}
