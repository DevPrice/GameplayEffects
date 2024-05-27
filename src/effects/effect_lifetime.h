#ifndef EFFECT_LIFETIME_H
#define EFFECT_LIFETIME_H

#include "binding_macros.h"
#include "effects/gameplay_requirements.h"
#include "effects/time_source.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectLifetime : public Resource {
    GDCLASS(EffectLifetime, Resource)

    GET_SET_PROPERTY(TypedArray<GameplayRequirements>, ongoing_requirements)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, duration)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, period)
    GET_SET_PROPERTY(bool, execute_on_application)
    GET_SET_PROPERTY(Ref<TimeSource>, time_source)

public:
    EffectLifetime();

protected:
    static void _bind_methods();
};

#endif
