#ifndef MODIFIER_MAGNITUDE_H
#define MODIFIER_MAGNITUDE_H

#include "binding_macros.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ModifierMagnitude : public Resource {
    GDCLASS(ModifierMagnitude, Resource)

public:
    virtual float get_magnitude() = 0;

protected:
    static void _bind_methods();
};

#endif
