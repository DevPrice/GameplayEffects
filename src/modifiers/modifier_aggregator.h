#ifndef MODIFIER_AGGREGATOR_H
#define MODIFIER_AGGREGATOR_H

#include "stats/gameplay_stat.h"
#include "modifiers/evaluated_modifier.h"

#include <vector>
#include <memory>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class ModifierAggregator {

private:
    std::vector<std::shared_ptr<EvaluatedModifier>> modifiers;

public:
    ModifierAggregator() { }
    ModifierAggregator(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers) : modifiers(p_modifiers) { }

    void add_modifier(const std::shared_ptr<EvaluatedModifier>& modifier);
    void add_modifiers(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers);
    bool get_modified_value(const Ref<GameplayStat>& stat, float base_value, float& modified_value) const;
    float get_modified_value(const Ref<GameplayStat>& stat, float base_value) const;

private:
    bool get_modified_value(const Ref<ModifierChannel>& channel, const Ref<GameplayStat>& stat, float base_value, float& modified_value) const;
};

#endif
