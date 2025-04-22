#include "effects/effect_application_context.h"

#include "modifiers/modifier_magnitude.h"

void ModifierMagnitude::_bind_methods() {
    GDVIRTUAL_BIND(get_magnitude, "context")
}

stat_value_t ModifierMagnitude::get_magnitude(const Ref<EffectApplicationContext>& context) const {
    stat_value_t magnitude{};
    GDVIRTUAL_CALL(get_magnitude, context, magnitude);
    return magnitude;
}

GDVIRTUAL1RC_IMPL(ModifierMagnitude, stat_value_t, get_magnitude, Ref<EffectApplicationContext>)
