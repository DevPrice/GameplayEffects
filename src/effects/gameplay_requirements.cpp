#include "binding_macros.h"
#include "effects/effect_application_context.h"
#include "effects/gameplay_requirements.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayRequirements::_bind_methods() {
    GDVIRTUAL_BIND(_requirements_met, "context")
}

bool GameplayRequirements::requirements_met(const Ref<EffectApplicationContext>& application_context) {
    bool result = true;
    GDVIRTUAL_REQUIRED_CALL(_requirements_met, application_context, result);
    return result;
}

GDVIRTUAL1R_IMPL(GameplayRequirements, bool, _requirements_met, Ref<EffectApplicationContext>)
