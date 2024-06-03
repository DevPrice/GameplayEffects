#ifndef MODIFIER_CHANNEL_H
#define MODIFIER_CHANNEL_H

#include "binding_macros.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ModifierChannel : public Resource {
    GDCLASS(ModifierChannel, Resource)

    GET_SET_PROPERTY(int32_t, priority)

public:
    ModifierChannel() : priority(0) { }

protected:
    static void _bind_methods();
};

#endif
