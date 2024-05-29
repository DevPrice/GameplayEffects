#ifndef STAT_EVALUATOR_H
#define STAT_EVALUATOR_H

#include "binding_macros.h"
#include "effects/effect_execution_context.h"
#include "stats/captured_stat.h"

#include <godot_cpp/classes/resource.hpp>
#include <memory>

using namespace godot;

class CapturedStatEvaluator {
private:
    const EffectExecutionContext execution_context;

    ActorSnapshot get_snapshot(Ref<CapturedStat> stat) const;

public:
    CapturedStatEvaluator(EffectExecutionContext effect_execution_context);

    float get_base_value(Ref<CapturedStat> stat) const;
    float get_current_value(Ref<CapturedStat> stat) const;
    float get_modified_value(Ref<CapturedStat> stat, float base_value) const;
};

class StatEvaluator : public RefCounted {
    GDCLASS(StatEvaluator, RefCounted)

private:
    std::unique_ptr<CapturedStatEvaluator> stat_evaluator;

public:
    void set_evaluator(const CapturedStatEvaluator& evaluator);

    float get_base_value(Ref<CapturedStat> stat) const;
    float get_current_value(Ref<CapturedStat> stat) const;
    float get_modified_value(Ref<CapturedStat> stat, float base_value) const;

protected:
    static void _bind_methods();
};

#endif
