#include "modifiers/modifier_channel.h"

void ModifierChannel::_bind_methods() {
    BIND_GET_SET(ModifierChannel, priority, Variant::INT)
}

GET_SET_PROPERTY_IMPL(ModifierChannel, int32_t, priority)
