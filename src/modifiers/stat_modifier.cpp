#include "modifiers/stat_modifier.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void StatModifier::_bind_methods() {
    BIND_ENUM_CONSTANT(Offset)
    BIND_ENUM_CONSTANT(Multiply)
    BIND_ENUM_CONSTANT(Override)
    BIND_GET_SET_ENUM(StatModifier, operation, "Offset:0,Multiply:1,Override:2")
    BIND_GET_SET_RESOURCE(StatModifier, stat, GameplayStat)
}

GET_SET_PROPERTY_IMPL(StatModifier, Ref<GameplayStat>, stat)
GET_SET_PROPERTY_IMPL(StatModifier, StatModifier::Operation, operation)
