#ifndef EFFECT_LIFETIME_H
#define EFFECT_LIFETIME_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectLifetime : public Resource {
    GDCLASS(EffectLifetime, Resource)

    GET_SET_PROPERTY(Ref<ModifierMagnitude>, duration)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, period)
    GET_SET_PROPERTY(bool, execute_on_application)

protected:
    static void _bind_methods();
};

#endif
