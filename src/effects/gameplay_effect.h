#ifndef GAMEPLAY_EFFECT_H
#define GAMEPLAY_EFFECT_H

#include "binding_macros.h"
#include "modifiers/stat_modifier.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class GameplayEffect : public Resource {
    GDCLASS(GameplayEffect, Resource)

    GET_SET_PROPERTY(TypedArray<StatModifier>, modifiers)

protected:
    static void _bind_methods();
};

#endif
