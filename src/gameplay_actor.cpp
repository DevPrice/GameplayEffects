#include "gameplay_actor.h"
#include "binding_macros.h"
#include "containers.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GameplayActor::_bind_methods() {
    ADD_SIGNAL(MethodInfo("receiving_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    ADD_SIGNAL(MethodInfo("received_effect", PropertyInfo(Variant::OBJECT, "spec", PROPERTY_HINT_RESOURCE_TYPE, "GameplayEffectSpec")));
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
    BIND_STATIC_METHOD(GameplayActor, find_actor_for_node, "node")
    BIND_METHOD(GameplayActor, make_effect_spec, "effect");
    BIND_METHOD(GameplayActor, apply_effect_to_self, "effect");
    BIND_METHOD(GameplayActor, apply_effect_to_target, "effect", "target");
    BIND_METHOD(GameplayActor, apply_effect_spec, "spec");
    // TODO: Support override virtuals in gdscript
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

    const EffectExecutionContext execution_context = _make_execution_context(spec);

    const TypedArray<GameplayRequirements> application_requirements = spec->get_effect()->get_application_requirements();
    const bool requirements_met = array_all_of(application_requirements, [&execution_context](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || !requirements->requirements_met(execution_context);
    });
    if (!requirements_met) return;

    emit_signal("receiving_effect", spec);

    // TODO: Period

    const ActiveEffect active_effect = ActiveEffect{spec, this, execution_context};
    execute_effect(active_effect);

    emit_signal("received_effect", spec);

    // TODO: Duration
}

void GameplayActor::execute_effect(const ActiveEffect& active_effect) {
    // TODO: Ongoing requirements
    // TODO: Capture modifier snapshot
    // TODO: Run executions
    // TODO: Update base stats
    // TODO: Recalculate stats
}

GameplayActor* GameplayActor::find_actor_for_node(Node* node) {
    GameplayActor* as_actor = Object::cast_to<GameplayActor>(node);
    if (as_actor) return as_actor;
    // TODO: Handle avatar
    return nullptr;
}

GET_SET_PROPERTY_IMPL(GameplayActor, TypedArray<GameplayStat>, stats)
