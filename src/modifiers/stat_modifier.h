#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "binding_macros.h"
#include "stats/gameplay_stat.h"

using namespace godot;

class StatModifier : public Resource {
    GDCLASS(StatModifier, Resource)

public:
    enum Operation {
        Offset = 0,
        Multiply = 1,
        Override = 2,
    };

    GET_SET_PROPERTY(Operation, operation)
    GET_SET_PROPERTY(Ref<GameplayStat>, stat)

protected:
    static void _bind_methods();
};

VARIANT_ENUM_CAST(StatModifier::Operation)

#endif
