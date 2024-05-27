#include "evaluated_modifier.h"
#include "containers.h"

bool ModifierSnapshot::requirements_met() const {
    Ref<EffectLifetime> lifetime = execution_context.spec->get_effect()->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [this](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(execution_context);
        });
        if (!requirements_met) return false;
    }
    return true;
}
