#include "gameplay_actor.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayActor::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
    ClassDB::bind_method(D_METHOD("make_effect_spec"), &GameplayActor::make_effect_spec);
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

GET_SET_PROPERTY_IMPL(GameplayActor, TypedArray<GameplayStat>, stats)
