#include "constant_magnitude.h"

#include <godot_cpp/core/class_db.hpp>

void ConstantMagnitude::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_magnitude"), &ConstantMagnitude::get_constant_magnitude);
    ClassDB::bind_method(D_METHOD("set_magnitude", "p_magnitude"), &ConstantMagnitude::set_constant_magnitude);
    ClassDB::add_property("ConstantMagnitude", PropertyInfo(Variant::FLOAT, "magnitude"), "set_magnitude", "get_magnitude");
}

ConstantMagnitude::ConstantMagnitude() {
    constant_magnitude = stat_value_t{};
}

stat_value_t ConstantMagnitude::get_magnitude(const Ref<EffectExecutionContext>& context) {
    return constant_magnitude;
}

GET_SET_PROPERTY_IMPL(ConstantMagnitude, stat_value_t, constant_magnitude)
