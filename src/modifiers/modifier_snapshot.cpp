#include "modifiers/modifier_snapshot.h"
#include "containers.h"

ModifierSnapshot::ModifierSnapshot(const Ref<StatModifier>& p_modifier, const Ref<EffectExecutionContext>& p_execution_context, stat_value_t p_magnitude)
    : modifier(p_modifier), execution_context(p_execution_context), magnitude(p_magnitude) { }

bool ModifierSnapshot::requirements_met() const {
    Ref<EffectLifetime> lifetime = execution_context->get_spec()->get_effect()->get_lifetime();
    if (lifetime.is_valid()) {
        const TypedArray<GameplayRequirements> ongoing_requirements = lifetime->get_ongoing_requirements();
        const bool requirements_met = array_all_of(ongoing_requirements, [this](Ref<GameplayRequirements> requirements) {
            return !requirements.is_valid() || requirements->requirements_met(execution_context);
        });
        if (!requirements_met) return false;
    }

    return array_all_of(modifier->get_requirements(), [this](Ref<GameplayRequirements> requirements) {
        return !requirements.is_valid() || requirements->requirements_met(execution_context);
    });
}
