#include "effects/gameplay_effect.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayEffect::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, modifiers, StatModifier)
}

GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<StatModifier>, modifiers)