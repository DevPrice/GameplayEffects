#include "effects/effect_lifetime.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void EffectLifetime::_bind_methods() {
    BIND_GET_SET_RESOURCE(EffectLifetime, duration, ModifierMagnitude)
    BIND_GET_SET_RESOURCE(EffectLifetime, period, ModifierMagnitude)
    BIND_GET_SET(EffectLifetime, execute_on_application, Variant::BOOL)
}

GET_SET_PROPERTY_IMPL(EffectLifetime, Ref<ModifierMagnitude>, duration)
GET_SET_PROPERTY_IMPL(EffectLifetime, Ref<ModifierMagnitude>, period)
GET_SET_PROPERTY_IMPL(EffectLifetime, bool, execute_on_application)
