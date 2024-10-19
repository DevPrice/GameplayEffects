#include "modifiers/custom_magnitude_calculation.h"

using namespace godot;

void CustomMagnitudeCalculation::_bind_methods() {
    GDVIRTUAL_BIND(_get_magnitude, "context");
}

stat_value_t CustomMagnitudeCalculation::get_magnitude(const Ref<EffectExecutionContext>& context) {
    stat_value_t magnitude = 0.f;
    if (GDVIRTUAL_CALL(_get_magnitude, context, magnitude)) {
        return magnitude;
    }
    return 0.f;
}
