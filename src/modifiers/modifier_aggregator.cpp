#include "modifiers/modifier_aggregator.h"
#include "modifiers/evaluated_modifier.h"

#include <algorithm>
#include <numeric>

void ModifierAggregator::add_modifier(const std::shared_ptr<EvaluatedModifier>& modifier) {
    modifiers.push_back(modifier);
}

void ModifierAggregator::add_modifiers(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers) {
    modifiers.insert(modifiers.end(), p_modifiers.begin(), p_modifiers.end());
}

bool ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, float base_value, float& modified_value) const {
    std::vector<std::shared_ptr<EvaluatedModifier>> relevant_modifiers;
    std::copy_if(modifiers.begin(), modifiers.end(), std::back_inserter(relevant_modifiers), [&stat](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_stat() == stat && modifier->requirements_met();
    });

    // Return the last Override, if present
    for (int i = relevant_modifiers.size() - 1; i >= 0; i--) {
        std::shared_ptr<EvaluatedModifier> modifier = relevant_modifiers[i];
        if (modifier->get_operation() == StatModifier::Operation::Override) {
            modified_value = modifier->get_magnitude();
            return true;
        }
    }

    std::vector<std::shared_ptr<EvaluatedModifier>> offset_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(offset_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Offset;
    });
    float aggregate_offset = std::accumulate(offset_modifiers.begin(), offset_modifiers.end(), 0.f, [](const float acc, const std::shared_ptr<EvaluatedModifier> modifier) {
        return acc + modifier->get_magnitude();
    });

    std::vector<std::shared_ptr<EvaluatedModifier>> multiply_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(multiply_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Multiply;
    });
    float aggregate_multiply = 1.f + std::accumulate(multiply_modifiers.begin(), multiply_modifiers.end(), 0.f, [](const float acc, const std::shared_ptr<EvaluatedModifier> modifier) {
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
