#include "modifiers/modifier_snapshot.h"
#include "containers.h"

ModifierSnapshot::ModifierSnapshot(const Ref<StatModifier>& p_modifier, const Ref<EffectApplicationContext>& p_application_context, stat_value_t p_magnitude)
    : modifier(p_modifier), application_context(p_application_context), magnitude(p_magnitude) { }

bool ModifierSnapshot::requirements_met() const {
    Ref<EffectLifetime> lifetime = application_context->get_spec()->get_effect()->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [this](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(application_context);
        });
        if (!requirements_met) return false;
    }

    return array_all_of(modifier->get_requirements(), [this](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || requirements->requirements_met(application_context);
    });
}
