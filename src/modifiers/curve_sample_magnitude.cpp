#include "modifiers/curve_sample_magnitude.h"

void CurveSampleMagnitude::_bind_methods() {
    BIND_GET_SET_RESOURCE(CurveSampleMagnitude, offset, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(CurveSampleMagnitude, curve, Curve)
}

CurveSampleMagnitude::CurveSampleMagnitude() { }

stat_value_t CurveSampleMagnitude::get_magnitude(const Ref<EffectApplicationContext>& context) const {
    if (offset.is_null() || curve.is_null()) return stat_value_t{};

    stat_value_t offset_magnitude = offset->get_magnitude(context);
    return curve->sample(offset_magnitude);
}

GET_SET_PROPERTY_IMPL(CurveSampleMagnitude, Ref<ModifierMagnitude>, offset)
GET_SET_PROPERTY_IMPL(CurveSampleMagnitude, Ref<Curve>, curve)
