#include "stats/captured_stat_evaluator.h"
#include "effects/effect_execution_context.h"
#include "gameplay_actor.h"
#include "modifiers/modifier_aggregator.h"

#include <godot_cpp/variant/utility_functions.hpp>

CapturedStatEvaluator::CapturedStatEvaluator(EffectExecutionContext effect_execution_context)
    : execution_context(effect_execution_context) {}

ActorSnapshot CapturedStatEvaluator::get_snapshot(Ref<CapturedStat> stat) const {
    if (stat.is_valid()) {
        if (stat->get_capture_from() == CapturedStat::CaptureSource::Target) {
            if (stat->get_snapshot()) {
                return execution_context.target_snapshot;
            }
            if (execution_context.target_actor) {
                return execution_context.target_actor->capture_snapshot();
            }
        } else {
            Ref<GameplayEffectContext> effect_context = execution_context.spec->get_context();
            if (effect_context.is_valid()) {
                if (stat->get_snapshot()) {
                    if (std::unique_ptr<ActorSnapshot> actor_snapshot = effect_context->get_source_snapshot()) {
                        return *actor_snapshot;
                    }
                }
                if (const GameplayActor* source_actor = effect_context->get_source_actor()) {
                    return source_actor->capture_snapshot();
                }
            }
        }
    }
    UtilityFunctions::push_error("Invalid effect spec state! Unable to get actor snapshot.");
    return ActorSnapshot{};
}

float CapturedStatEvaluator::get_base_value(Ref<CapturedStat> stat) const {
    if (stat.is_valid() && stat->get_stat().is_valid()) {
        ActorSnapshot snapshot = get_snapshot(stat);
        if (const StatSnapshot* stat_snapshot = snapshot.base_value_snapshot.getptr(stat->get_stat())) {
            return stat_snapshot->base_value;
        }
        return stat->get_stat()->get_base_value();
    }
    UtilityFunctions::push_error("Captured stat is invalid! Unable to get stat base value.");
    return 0.0f;
}

float CapturedStatEvaluator::get_current_value(Ref<CapturedStat> stat) const {
    if (stat.is_valid() && stat->get_stat().is_valid()) {
        ActorSnapshot snapshot = get_snapshot(stat);
        ModifierAggregator aggregator{snapshot.modifier_snapshot};
        if (const StatSnapshot* stat_snapshot = snapshot.base_value_snapshot.getptr(stat->get_stat())) {
            return aggregator.get_modified_value(stat->get_stat(), stat_snapshot->base_value);
        }
        return aggregator.get_modified_value(stat->get_stat(), stat->get_stat()->get_base_value());
    }
    UtilityFunctions::push_error("Captured stat is invalid! Unable to get stat current value.");
    return 0.0f;
}

float CapturedStatEvaluator::get_modified_value(Ref<CapturedStat> stat, float base_value) const {
    if (stat.is_valid() && stat->get_stat().is_valid()) {
        ActorSnapshot snapshot = get_snapshot(stat);
        ModifierAggregator aggregator{snapshot.modifier_snapshot};
        return aggregator.get_modified_value(stat->get_stat(), base_value);
    }
    UtilityFunctions::push_error("Captured stat is invalid! Unable to get stat current value.");
    return 0.0f;
}
