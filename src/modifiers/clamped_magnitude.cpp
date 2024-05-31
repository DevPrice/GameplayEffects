#include "modifiers/clamped_magnitude.h"
#include "effects/effect_execution_context.h"

#include <algorithm>
#include "clamped_magnitude.h"

void ClampedMagnitude::_bind_methods() {
    BIND_GET_SET_RESOURCE(ClampedMagnitude, value, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(ClampedMagnitude, min_value, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(ClampedMagnitude, max_value, ModifierMagnitude)
}

ClampedMagnitude::ClampedMagnitude() { }

float ClampedMagnitude::get_magnitude(const Ref<EffectExecutionContext>& context) {
    float value_magnitude = value.is_valid() ? value->get_magnitude(context) : 0.f;
    if (min_value.is_valid()) {
        float min_value_magnitude = min_value->get_magnitude(context);
        if (value_magnitude < min_value_magnitude) return min_value_magnitude;
    }
    if (max_value.is_valid()) {
        float max_value_magnitude = max_value->get_magnitude(context);
        if (value_magnitude > max_value_magnitude) return max_value_magnitude;
    }
    return value_magnitude;
}

GET_SET_PROPERTY_IMPL(ClampedMagnitude, Ref<ModifierMagnitude>, value)
GET_SET_PROPERTY_IMPL(ClampedMagnitude, Ref<ModifierMagnitude>, min_value)
GET_SET_PROPERTY_IMPL(ClampedMagnitude, Ref<ModifierMagnitude>, max_value)
