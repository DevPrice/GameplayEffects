#include "modifiers/modifier_aggregator.h"
#include "modifiers/evaluated_modifier.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <algorithm>
#include <numeric>

ModifierAggregator::ModifierAggregator(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers) {
    add_modifiers(p_modifiers);
}

void ModifierAggregator::add_modifier(const std::shared_ptr<EvaluatedModifier>& modifier) {
    std::vector<std::shared_ptr<EvaluatedModifier>>& channel_modifiers = modifiers[modifier->get_channel()];
    channel_modifiers.push_back(modifier);
}

void ModifierAggregator::add_modifiers(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers) {
    for (const std::shared_ptr<EvaluatedModifier>& modifier : p_modifiers) {
        add_modifier(modifier);
    }
}

bool ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, stat_value_t base_value, stat_value_t& out_modified_value) const {
    bool modified = false;
    out_modified_value = base_value;
    for (auto& [channel, _] : modifiers) {
        modified |= get_modified_value(channel, stat, out_modified_value, out_modified_value);
    }
    return modified;
}

stat_value_t ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, stat_value_t base_value) const {
    stat_value_t modified_value{};
    get_modified_value(stat, base_value, modified_value);
    return modified_value;
}

bool ModifierAggregator::get_modified_value(const Ref<ModifierChannel>& channel, const Ref<GameplayStat>& stat, stat_value_t base_value, stat_value_t& out_modified_value) const {
    const std::vector<std::shared_ptr<EvaluatedModifier>>& channel_modifiers = modifiers.at(channel);
    std::vector<std::shared_ptr<EvaluatedModifier>> relevant_modifiers;
    std::copy_if(channel_modifiers.begin(), channel_modifiers.end(), std::back_inserter(relevant_modifiers), [&stat](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_stat() == stat && modifier->requirements_met();
    });

    // Return the last Override, if present
    for (int i = relevant_modifiers.size() - 1; i >= 0; i--) {
        std::shared_ptr<EvaluatedModifier> modifier = relevant_modifiers[i];
        if (modifier->get_operation() == StatModifier::Operation::Override) {
            out_modified_value = modifier->get_magnitude();
            return true;
        }
    }

    std::vector<std::shared_ptr<EvaluatedModifier>> offset_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(offset_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Offset;
    });
    stat_value_t aggregate_offset = std::accumulate(offset_modifiers.begin(), offset_modifiers.end(), stat_value_t{}, [](const stat_value_t acc, const std::shared_ptr<EvaluatedModifier> modifier) {
        return acc + modifier->get_magnitude();
    });

    std::vector<std::shared_ptr<EvaluatedModifier>> multiply_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(multiply_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Multiply;
    });
    stat_value_t aggregate_multiply = 1.f + std::accumulate(multiply_modifiers.begin(), multiply_modifiers.end(), stat_value_t{}, [](const stat_value_t acc, const std::shared_ptr<EvaluatedModifier> modifier) {
        return acc + modifier->get_magnitude() - 1.f;
    });

    out_modified_value = (base_value + aggregate_offset) * aggregate_multiply;

    return aggregate_offset != stat_value_t{} || aggregate_multiply != 1.f;
}
