#include "modifiers/scaled_magnitude.h"

void ScaledMagnitude::_bind_methods(){
    BIND_GET_SET_RESOURCE(ScaledMagnitude, base, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(ScaledMagnitude, premultiply_offset, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(ScaledMagnitude, postmultiply_offset, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(ScaledMagnitude, coefficient, ModifierMagnitude)
}

ScaledMagnitude::ScaledMagnitude() { }

stat_value_t ScaledMagnitude::get_magnitude(const Ref<EffectExecutionContext>& context) const {
    stat_value_t base_magnitude = base.is_valid() ? base->get_magnitude(context) : stat_value_t{};
    stat_value_t premultiply_offset_magnitude = premultiply_offset.is_valid() ? premultiply_offset->get_magnitude(context) : stat_value_t{};
    stat_value_t postmultiply_offset_magnitude = postmultiply_offset.is_valid() ? postmultiply_offset->get_magnitude(context) : stat_value_t{};
    stat_value_t coefficient_magnitude = coefficient.is_valid() ? coefficient->get_magnitude(context) : 1.f;
    return (base_magnitude + premultiply_offset_magnitude) * coefficient_magnitude + postmultiply_offset_magnitude;
}

GET_SET_PROPERTY_IMPL(ScaledMagnitude, Ref<ModifierMagnitude>, base)
GET_SET_PROPERTY_IMPL(ScaledMagnitude, Ref<ModifierMagnitude>, premultiply_offset)
GET_SET_PROPERTY_IMPL(ScaledMagnitude, Ref<ModifierMagnitude>, postmultiply_offset)
GET_SET_PROPERTY_IMPL(ScaledMagnitude, Ref<ModifierMagnitude>, coefficient)
