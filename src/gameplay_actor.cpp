#include "gameplay_actor.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GameplayActor::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
    BIND_METHOD(GameplayActor, make_effect_spec);
    BIND_METHOD(GameplayActor, apply_effect_to_self, "effect");
    BIND_METHOD(GameplayActor, apply_effect_to_target, "effect", "target");
    BIND_METHOD(GameplayActor, apply_effect_spec, "spec");
    // TODO: Support override virtuals in gdscript
}

Ref<GameplayEffectSpec> GameplayActor::make_effect_spec() {
    auto spec = memnew(GameplayEffectSpec);
    spec->set_context(_make_effect_context());
    return spec;
}

GameplayEffectContext GameplayActor::_make_effect_context() {
    return GameplayEffectContext { this };
}

EffectExecutionContext GameplayActor::_make_execution_context(Ref<GameplayEffectSpec>& spec)
{
    return EffectExecutionContext { spec, this };
}

void GameplayActor::apply_effect_to_self(Ref<GameplayEffect> effect) {
    apply_effect_to_target(effect, this);
}

void GameplayActor::apply_effect_to_target(Ref<GameplayEffect> effect, Node* target) {
    GameplayActor* target_actor = find_actor_for_node(target);
    if (target_actor) {
        target_actor->apply_effect_spec(make_effect_spec());
    }
}

void GameplayActor::apply_effect_spec(Ref<GameplayEffectSpec> spec) {
    // TODO
    UtilityFunctions::print("SPEC APPLIED!");
}

GameplayActor* GameplayActor::find_actor_for_node(Node* node) {
    auto as_actor = Object::cast_to<GameplayActor>(node);
    if (as_actor) return as_actor;
    // TODO: Handle avatar
    return nullptr;
}

GET_SET_PROPERTY_IMPL(GameplayActor, TypedArray<GameplayStat>, stats)
