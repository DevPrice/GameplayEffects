#include "modifiers/modifier_magnitude.h"
#include "effects/effect_execution_context.h"

void ModifierMagnitude::_bind_methods() {
    BIND_METHOD(ModifierMagnitude, get_magnitude, "execution_context");
}
