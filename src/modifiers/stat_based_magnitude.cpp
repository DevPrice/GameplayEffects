#include "modifiers/stat_based_magnitude.h"
#include "stats/captured_stat_evaluator.h"

void StatBasedMagnitude::_bind_methods() {
    BIND_ENUM_CONSTANT(Base)
    BIND_ENUM_CONSTANT(Current)
    BIND_ENUM_CONSTANT(Bonus)
    BIND_GET_SET_RESOURCE(StatBasedMagnitude, captured_stat, CapturedStat)
    BIND_GET_SET_ENUM(StatBasedMagnitude, value_type, "Base:0,Current:1,Bonus:2")
}

StatBasedMagnitude::StatBasedMagnitude() : value_type(StatValueType::Current) { }

float StatBasedMagnitude::get_magnitude(const Ref<EffectExecutionContext>& context) {
    if (captured_stat.is_null()) return 0.f;

    CapturedStatEvaluator stat_evaluator(context);
    if (value_type == StatValueType::Base) {
        return stat_evaluator.get_base_value(captured_stat);
    }
    if (value_type == StatValueType::Bonus) {
        return stat_evaluator.get_current_value(captured_stat) - stat_evaluator.get_base_value(captured_stat);
    }
    return stat_evaluator.get_current_value(captured_stat);
}

GET_SET_PROPERTY_IMPL(StatBasedMagnitude, Ref<CapturedStat>, captured_stat)
GET_SET_PROPERTY_IMPL(StatBasedMagnitude, StatBasedMagnitude::StatValueType, value_type)
