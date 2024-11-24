#include "effects/gameplay_effect.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

#include "effect_tags_component.h"

using namespace godot;

void GameplayEffect::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, application_requirements, GameplayRequirements)
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, modifiers, StatModifier)
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, executions, EffectExecution)
    BIND_GET_SET_RESOURCE_ARRAY(GameplayEffect, components, EffectComponent)
    BIND_GET_SET_RESOURCE(GameplayEffect, lifetime, EffectLifetime)
    BIND_METHOD(GameplayEffect, get_effect_tags)
}

bool GameplayEffect::is_instant() const {
    return lifetime == nullptr;
}

TypedArray<String> GameplayEffect::get_effect_tags() const {
    TypedArray<String> tags;
    for (size_t i = 0; i < components.size(); i++) {
        if (const auto tags_component = cast_to<EffectTagsComponent>(components[i])) {
            tags.append_array(tags_component->get_effect_tags());
        }
    }
    return tags;
}

GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<GameplayRequirements>, application_requirements)
GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<StatModifier>, modifiers)
GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<EffectExecution>, executions)
GET_SET_PROPERTY_IMPL(GameplayEffect, TypedArray<EffectComponent>, components)
GET_SET_PROPERTY_IMPL(GameplayEffect, Ref<EffectLifetime>, lifetime)
