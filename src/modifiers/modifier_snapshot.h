#ifndef MODIFIER_SNAPSHOT_H
#define MODIFIER_SNAPSHOT_H

#include "effects/effect_execution_context.h"
#include "modifiers/stat_modifier.h"
#include "modifiers/evaluated_modifier.h"

class ModifierSnapshot : public EvaluatedModifier {

    Ref<StatModifier> modifier;
    EffectExecutionContext execution_context;
    float magnitude;

public:
    ModifierSnapshot(Ref<StatModifier> p_modifier, EffectExecutionContext p_execution_context, float p_magnitude);

    Ref<GameplayStat> get_stat() const override { return modifier->get_stat(); }
    StatModifier::Operation get_operation() const override { return modifier->get_operation(); }
    float get_magnitude() const override { return magnitude; }
    bool requirements_met() const override;
};

#endif
