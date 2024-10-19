#ifndef MODIFIER_SNAPSHOT_H
#define MODIFIER_SNAPSHOT_H

#include "typedefs.h"
#include "effects/effect_execution_context.h"
#include "modifiers/stat_modifier.h"
#include "modifiers/evaluated_modifier.h"
#include "modifiers/modifier_channel.h"

class ModifierSnapshot : public EvaluatedModifier {

    const Ref<StatModifier> modifier;
    const Ref<EffectExecutionContext> execution_context;
    const stat_value_t magnitude;

public:
    ModifierSnapshot(const Ref<StatModifier>& p_modifier, const Ref<EffectExecutionContext>& p_execution_context, stat_value_t p_magnitude);

    Ref<GameplayStat> get_stat() const override { return modifier->get_stat(); }
    StatModifier::Operation get_operation() const override { return modifier->get_operation(); }
    stat_value_t get_magnitude() const override { return magnitude; }
    Ref<ModifierChannel> get_channel() const override { return modifier->get_channel(); }
    bool requirements_met() const override;
};

#endif
