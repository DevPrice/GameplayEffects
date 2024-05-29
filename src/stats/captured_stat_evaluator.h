#ifndef CAPTURED_STAT_EVALUATOR_H
#define CAPTURED_STAT_EVALUATOR_H

#include "binding_macros.h"
#include "effects/effect_execution_context.h"

using namespace godot;

class CapturedStatEvaluator {
private:
    const EffectExecutionContext execution_context;

    ActorSnapshot get_snapshot(const Ref<CapturedStat>& stat) const;

public:
    CapturedStatEvaluator(EffectExecutionContext effect_execution_context);

    float get_base_value(const Ref<CapturedStat>& stat) const;
    float get_current_value(const Ref<CapturedStat>& stat) const;
    float get_modified_value(const Ref<CapturedStat>& stat, float base_value) const;
};

#endif
