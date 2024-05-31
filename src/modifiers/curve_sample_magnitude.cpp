#include "modifiers/curve_sample_magnitude.h"

void CurveSampleMagnitude::_bind_methods() {
    BIND_GET_SET_RESOURCE(CurveSampleMagnitude, offset, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(CurveSampleMagnitude, curve, Curve)
}

CurveSampleMagnitude::CurveSampleMagnitude() { }

float CurveSampleMagnitude::get_magnitude(const EffectExecutionContext& context) {
    if (offset.is_null() || curve.is_null()) return 0.f;

    float offset_magnitude = offset->get_magnitude(context);
    return curve->sample(offset_magnitude);
}

GET_SET_PROPERTY_IMPL(CurveSampleMagnitude, Ref<ModifierMagnitude>, offset)
GET_SET_PROPERTY_IMPL(CurveSampleMagnitude, Ref<Curve>, curve)
