#ifndef STAT_EVALUATOR_H
#define STAT_EVALUATOR_H

#include "binding_macros.h"
#include "stats/captured_stat.h"

#include <godot_cpp/classes/resource.hpp>
#include <memory>

class CapturedStatEvaluator;
class EffectExecutionContext;

using namespace godot;

class StatEvaluator : public RefCounted {
    GDCLASS(StatEvaluator, RefCounted)

private:
    const CapturedStatEvaluator* stat_evaluator;

public:
    void set_evaluator(const CapturedStatEvaluator* evaluator);

    float get_base_value(Ref<CapturedStat> stat) const;
    float get_current_value(Ref<CapturedStat> stat) const;
    float get_modified_value(Ref<CapturedStat> stat, float base_value) const;

protected:
    static void _bind_methods();
};

#endif
