#ifndef MODIFIER_MAGNITUDE_H
#define MODIFIER_MAGNITUDE_H

#include "binding_macros.h"
#include "typedefs.h"

#include <godot_cpp/classes/resource.hpp>

class EffectExecutionContext;

using namespace godot;

class ModifierMagnitude : public Resource {
    GDCLASS(ModifierMagnitude, Resource)

public:
    virtual stat_value_t get_magnitude(const Ref<EffectExecutionContext>& context) = 0;

protected:
    static void _bind_methods();
};

#endif
