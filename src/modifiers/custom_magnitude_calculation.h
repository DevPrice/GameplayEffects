#ifndef CUSTOM_MAGNITUDE_CALCULATION_H
#define CUSTOM_MAGNITUDE_CALCULATION_H

#include "binding_macros.h"
#include "effects/effect_execution_context.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

class CustomMagnitudeCalculation : public ModifierMagnitude {
    GDCLASS(CustomMagnitudeCalculation, ModifierMagnitude)

public:
    GDVIRTUAL1RC(float, _get_magnitude, Ref<EffectExecutionContext>)

    float get_magnitude(const Ref<EffectExecutionContext>& context) override;

protected:
    static void _bind_methods();
};

#endif
