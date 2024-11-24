#ifndef MODIFIER_MAGNITUDE_H
#define MODIFIER_MAGNITUDE_H

#include "binding_macros.h"
#include "virtual_macros.h"
#include "typedefs.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/resource.hpp>

class EffectApplicationContext;

using namespace godot;

class ModifierMagnitude : public Resource {
    GDCLASS(ModifierMagnitude, Resource)

public:
    virtual stat_value_t get_magnitude(const Ref<EffectApplicationContext>& context) const;

private:
    GDVIRTUAL1RC_NO_IMPL(stat_value_t, get_magnitude, const Ref<EffectApplicationContext>&)

protected:
    static void _bind_methods();
};

#endif
