#ifndef STAT_EVALUATOR_H
#define STAT_EVALUATOR_H

#include "binding_macros.h"
#include "typedefs.h"
#include "stats/captured_stat.h"

#include <godot_cpp/classes/resource.hpp>

class CapturedStatEvaluator;
class EffectExecutionContext;

using namespace godot;

class StatEvaluator : public RefCounted {
    GDCLASS(StatEvaluator, RefCounted)

private:
    const CapturedStatEvaluator* stat_evaluator;

public:
    void set_evaluator(const CapturedStatEvaluator* evaluator);

    stat_value_t get_base_value(Ref<CapturedStat> stat) const;
    stat_value_t get_current_value(Ref<CapturedStat> stat) const;
    stat_value_t get_modified_value(Ref<CapturedStat> stat, stat_value_t base_value) const;

protected:
    static void _bind_methods();
};

#endif
