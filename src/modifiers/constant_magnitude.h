#ifndef CONSTANT_MAGNITUDE_H
#define CONSTANT_MAGNITUDE_H

#include "binding_macros.h"
#include "typedefs.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ConstantMagnitude : public ModifierMagnitude {
    GDCLASS(ConstantMagnitude, ModifierMagnitude)

    GET_SET_PROPERTY(stat_value_t, constant_magnitude)

public:
    ConstantMagnitude();

    stat_value_t get_magnitude(const Ref<EffectExecutionContext>& context) override;

  protected:
    static void _bind_methods();
};

#endif
