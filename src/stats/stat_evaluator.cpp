#include "stats/stat_evaluator.h"
#include "gameplay_actor.h"
#include "modifiers/modifier_aggregator.h"
#include "stats/captured_stat_evaluator.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void StatEvaluator::_bind_methods() {
    BIND_METHOD(StatEvaluator, get_base_value, "stat")
    BIND_METHOD(StatEvaluator, get_current_value, "stat")
    BIND_METHOD(StatEvaluator, get_modified_value, "stat", "base_value")
}

void StatEvaluator::set_evaluator(const CapturedStatEvaluator *evaluator) {
    stat_evaluator = evaluator;
}

float StatEvaluator::get_base_value(Ref<CapturedStat> stat) const {
    if (stat_evaluator) {
        return stat_evaluator->get_base_value(stat);
    }
    UtilityFunctions::push_error("This StatEvaluator isn't associated with an effect execution!");
    return 0.0f;
}

float StatEvaluator::get_current_value(Ref<CapturedStat> stat) const {
    if (stat_evaluator) {
        return stat_evaluator->get_current_value(stat);
    }
    UtilityFunctions::push_error("This StatEvaluator isn't associated with an effect execution!");
    return 0.0f;
}

float StatEvaluator::get_modified_value(Ref<CapturedStat> stat, float base_value) const {
    if (stat_evaluator) {
        return stat_evaluator->get_modified_value(stat, base_value);
    }
    UtilityFunctions::push_error("This StatEvaluator isn't associated with an effect execution!");
    return 0.0f;
}
