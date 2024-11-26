#include "modifiers/modifier_aggregator.h"
#include "modifiers/evaluated_modifier.h"

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

bool ModifierAggregator::get_modified_value(const Ref<GameplayStat>& stat, const stat_value_t base_value, stat_value_t& out_modified_value) const {
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
    for (int i = relevant_modifiers.size() - 1; i >= 0; --i) {
        const std::shared_ptr<EvaluatedModifier> modifier = relevant_modifiers[i];
        if (modifier->get_operation() == StatModifier::Operation::Override) {
            out_modified_value = modifier->get_magnitude();
            return true;
        }
    }

    std::vector<std::shared_ptr<EvaluatedModifier>> offset_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(offset_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Offset;
    });

    stat_value_t aggregate_offset;
    if (channel.is_valid() && channel->_gdvirtual_aggregate_offset_overridden()) {
        PackedFloat64Array offset_magnitudes;
        for (auto it = offset_modifiers.begin(); it != offset_modifiers.end(); ++it) {
            offset_magnitudes.push_back((*it)->get_magnitude());
        }
        channel->_gdvirtual_aggregate_offset_call<false>(stat, offset_magnitudes, aggregate_offset);
    } else {
        std::vector<stat_value_t> offset_magnitudes;
        offset_magnitudes.reserve(offset_modifiers.size());
        std::transform(offset_modifiers.begin(), offset_modifiers.end(), std::back_inserter(offset_magnitudes), [](auto element) {
            return element->get_magnitude();
        });
        aggregate_offset = aggregate_with_bias(offset_magnitudes, 0.f);
    }

    std::vector<std::shared_ptr<EvaluatedModifier>> multiply_modifiers;
    std::copy_if(relevant_modifiers.begin(), relevant_modifiers.end(), std::back_inserter(multiply_modifiers), [](const std::shared_ptr<EvaluatedModifier> modifier) {
        return modifier && modifier->get_operation() == StatModifier::Operation::Multiply;
    });

    stat_value_t aggregate_multiply;
    if (channel.is_valid() && channel->_gdvirtual_aggregate_multiply_overridden()) {
        PackedFloat64Array multiply_magnitudes;
        for (auto it = multiply_modifiers.begin(); it != multiply_modifiers.end(); ++it) {
            multiply_magnitudes.push_back((*it)->get_magnitude());
        }
        channel->_gdvirtual_aggregate_multiply_call<false>(stat, multiply_magnitudes, aggregate_multiply);
    } else {
        std::vector<stat_value_t> multiply_magnitudes;
        multiply_magnitudes.reserve(multiply_modifiers.size());
        std::transform(multiply_modifiers.begin(), multiply_modifiers.end(), std::back_inserter(multiply_magnitudes), [](auto element) {
            return element->get_magnitude();
        });
        aggregate_multiply = aggregate_with_bias(multiply_magnitudes, 1.f);
    }

    out_modified_value = (base_value + aggregate_offset) * aggregate_multiply;

    return aggregate_offset != stat_value_t{} || aggregate_multiply != 1.f;
}

stat_value_t ModifierAggregator::aggregate_with_bias(const std::vector<stat_value_t>& modifier_values, stat_value_t bias) {
    return bias + std::accumulate(modifier_values.begin(), modifier_values.end(), stat_value_t{}, [bias](const stat_value_t acc, const stat_value_t modifier_magnitude) {
        return acc + modifier_magnitude - bias;
    });
}
