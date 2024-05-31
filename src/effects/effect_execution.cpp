#include "effects/effect_execution.h"
#include "effects/effect_execution_context.h"
#include "binding_macros.h"
#include "modifiers/evaluated_modifier.h"
#include "modifiers/stat_modifier.h"
#include "stats/gameplay_stat.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

void EffectExecutionOutput::_bind_methods() {
    BIND_METHOD(EffectExecutionOutput, add_modifier, "stat", "operation", "magnitude")
}

void EffectExecution::_bind_methods() {
    BIND_METHOD(EffectExecution, execute, "execution_context", "stat_evaluator", "output");
}

struct ExecutionEvaluatedModifier : public EvaluatedModifier {
    const Ref<GameplayStat> stat;
    const StatModifier::Operation operation = StatModifier::Operation::Offset;
    const float magnitude = 0.f;

    ExecutionEvaluatedModifier(Ref<GameplayStat> p_stat, StatModifier::Operation p_operation, float p_magnitude)
        : stat(p_stat), operation(p_operation), magnitude(p_magnitude) { }

    Ref<GameplayStat> get_stat() const override { return stat; }
    StatModifier::Operation get_operation() const override { return operation; }
    float get_magnitude() const override { return magnitude; }
    bool requirements_met() const override { return true; }
};

std::vector<std::shared_ptr<EvaluatedModifier>> EffectExecutionOutput::get_modifiers() const {
    return modifiers;
}

void EffectExecutionOutput::add_modifier(const Ref<GameplayStat>& stat, StatModifier::Operation operation, float magnitude) {
    modifiers.push_back(std::make_shared<ExecutionEvaluatedModifier>(stat, operation, magnitude));
}

