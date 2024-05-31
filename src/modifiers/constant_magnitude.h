#ifndef CONSTANT_MAGNITUDE_H
#define CONSTANT_MAGNITUDE_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ConstantMagnitude : public ModifierMagnitude {
    GDCLASS(ConstantMagnitude, ModifierMagnitude)

    GET_SET_PROPERTY(float, constant_magnitude)

public:
    ConstantMagnitude();

    float get_magnitude(const Ref<EffectExecutionContext>& context) override;

  protected:
    static void _bind_methods();
};

#endif
