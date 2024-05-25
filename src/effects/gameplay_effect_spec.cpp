#include "effects/gameplay_effect_spec.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayEffectSpec::_bind_methods() {
    
}

GET_SET_PROPERTY_IMPL(GameplayEffectSpec, Ref<GameplayEffect>, effect)
GET_SET_PROPERTY_IMPL(GameplayEffectSpec, GameplayEffectContext, context)
