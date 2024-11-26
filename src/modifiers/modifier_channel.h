#ifndef MODIFIER_CHANNEL_H
#define MODIFIER_CHANNEL_H

#include "typedefs.h"
#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

class GameplayStat;

using namespace godot;

class ModifierChannel : public Resource {
    GDCLASS(ModifierChannel, Resource)

    GET_SET_PROPERTY(int32_t, priority)

public:
    ModifierChannel() : priority(0) { }

    GDVIRTUAL2RC_NO_IMPL(stat_value_t, aggregate_offset, const Ref<GameplayStat>&, PackedFloat64Array)
    GDVIRTUAL2RC_NO_IMPL(stat_value_t, aggregate_multiply, const Ref<GameplayStat>&, PackedFloat64Array)

protected:
    static void _bind_methods();
};

#endif
