#ifndef MODIFIER_MAGNITUDE_H
#define MODIFIER_MAGNITUDE_H

#include "binding_macros.h"
#include "effects/effect_execution_context.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ModifierMagnitude : public Resource {
    GDCLASS(ModifierMagnitude, Resource)

public:
    virtual float get_magnitude(EffectExecutionContext& context) = 0;

protected:
    static void _bind_methods();
};

#endif
