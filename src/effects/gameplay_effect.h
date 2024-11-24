#ifndef GAMEPLAY_EFFECT_H
#define GAMEPLAY_EFFECT_H

#include "binding_macros.h"
#include "effects/effect_component.h"
#include "effects/effect_execution.h"
#include "effects/effect_lifetime.h"
#include "effects/gameplay_requirements.h"
#include "modifiers/stat_modifier.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class GameplayEffect : public Resource {
    GDCLASS(GameplayEffect, Resource)

    GET_SET_PROPERTY(TypedArray<GameplayRequirements>, application_requirements)
    GET_SET_PROPERTY(TypedArray<StatModifier>, modifiers)
    GET_SET_PROPERTY(TypedArray<EffectExecution>, executions)
    GET_SET_PROPERTY(TypedArray<EffectComponent>, components)
    GET_SET_PROPERTY(Ref<EffectLifetime>, lifetime)

public:
    bool is_instant() const;
    TypedArray<String> get_effect_tags() const;

protected:
    static void _bind_methods();
};

#endif
