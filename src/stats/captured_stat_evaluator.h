#ifndef CAPTURED_STAT_EVALUATOR_H
#define CAPTURED_STAT_EVALUATOR_H

#include "binding_macros.h"
#include "typedefs.h"
#include "effects/effect_application_context.h"

using namespace godot;

class CapturedStatEvaluator {
private:
    const Ref<EffectApplicationContext> application_context;

    ActorSnapshot get_snapshot(const Ref<CapturedStat>& stat) const;

public:
    CapturedStatEvaluator(const Ref<EffectApplicationContext>& effect_application_context);

    stat_value_t get_base_value(const Ref<CapturedStat>& stat) const;
    stat_value_t get_current_value(const Ref<CapturedStat>& stat) const;
    stat_value_t get_modified_value(const Ref<CapturedStat>& stat, stat_value_t base_value) const;
};

#endif
