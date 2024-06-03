#include "modifiers/custom_magnitude_calculation.h"

using namespace godot;

void CustomMagnitudeCalculation::_bind_methods() {
    GDVIRTUAL_BIND(_get_magnitude, "context");
}

float CustomMagnitudeCalculation::get_magnitude(const Ref<EffectExecutionContext>& context) {
    float magnitude = 0.f;
    if (GDVIRTUAL_CALL(_get_magnitude, context, magnitude)) {
        return magnitude;
    }
    return 0.f;
}
