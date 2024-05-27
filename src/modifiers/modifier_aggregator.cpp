#include "modifiers/modifier_aggregator.h"
#include "modifiers/evaluated_modifier.h"

#include <algorithm>
#include <numeric>

bool ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, float base_value, float& modified_value) const {
    std::vector<std::shared_ptr<IEvaluatedModifier>> relevant_modifiers;
    std::copy_if(modifiers.begin(), modifiers.end(), std::back_inserter(relevant_modifiers), [&stat](const std::shared_ptr<IEvaluatedModifier> modifier) {
        return modifier && modifier->get_stat() == stat && modifier->requirements_met();
    });

    // Return the last Override, if present
    for (int i = relevant_modifiers.size() - 1; i >= 0; i--) {
        std::shared_ptr<IEvaluatedModifier> modifier = relevant_modifiers[i];
        if (modifier->get_operation() == StatModifier::Operation::Override) {
            modified_value = modifier->get_magnitude();
            return true;
        }
    }

    std::vector<std::shared_ptr<IEvaluatedModifier>> offset_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(offset_modifiers), [](const std::shared_ptr<IEvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Offset;
    });
    float aggregate_offset = std::reduce(offset_modifiers.begin(), offset_modifiers.end(), 0.f, [](const float acc, const std::shared_ptr<IEvaluatedModifier> modifier) {
        return acc + modifier->get_magnitude();
    });

    std::vector<std::shared_ptr<IEvaluatedModifier>> multiply_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(multiply_modifiers), [](const std::shared_ptr<IEvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Multiply;
    });
    float aggregate_multiply = 1.f + std::reduce(offset_modifiers.begin(), offset_modifiers.end(), 0.f, [](const float acc, const std::shared_ptr<IEvaluatedModifier> modifier) {
        return acc + modifier->get_magnitude() - 1.f;
    });

    modified_value = (base_value + aggregate_offset) * aggregate_multiply;

    return aggregate_offset != 0.f || aggregate_multiply != 1.f;
}

float ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, float base_value) const {
    float modified_value = 0.f;
    get_modified_value(stat, base_value, modified_value);
    return modified_value;
}
