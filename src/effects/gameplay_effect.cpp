#include "effects/gameplay_effect.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayEffect::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, modifiers, StatModifier)
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, application_requirements, GameplayRequirements)
    BIND_GET_SET_RESOURCE(GameplayEffect, lifetime, EffectLifetime)
}

bool GameplayEffect::is_instant() const {
    return lifetime == nullptr;
}

GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<StatModifier>, modifiers)
GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<GameplayRequirements>, application_requirements)
GET_SET_PROPERTY_IMPL(GameplayEffect, Ref<EffectLifetime>, lifetime)
