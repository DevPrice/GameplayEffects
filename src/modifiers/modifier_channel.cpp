#include <stats/gameplay_stat.h>
#include "modifiers/modifier_channel.h"

void ModifierChannel::_bind_methods() {
    BIND_GET_SET(ModifierChannel, priority, Variant::INT)
    GDVIRTUAL_BIND(aggregate_offset, "stat", "offset_magnitudes")
    GDVIRTUAL_BIND(aggregate_multiply, "stat", "multiplier_magnitudes")
}

GET_SET_PROPERTY_IMPL(ModifierChannel, int32_t, priority)

GDVIRTUAL2RC_IMPL(ModifierChannel, stat_value_t, aggregate_offset, Ref<GameplayStat>, PackedFloat64Array)
GDVIRTUAL2RC_IMPL(ModifierChannel, stat_value_t, aggregate_multiply, Ref<GameplayStat>, PackedFloat64Array)
