#ifndef MODIFIER_AGGREGATOR_H
#define MODIFIER_AGGREGATOR_H

#include "stats/gameplay_stat.h"
#include "modifiers/evaluated_modifier.h"

#include <godot_cpp/classes/ref.hpp>
#include <map>
#include <memory>
#include <vector>

using namespace godot;

class ModifierAggregator {

private:
    struct ChannelPriorityCompare {
        bool operator()(const Ref<ModifierChannel>& a, const Ref<ModifierChannel>& b) const {
            if (a == b) return false;
            int32_t pa = a.is_valid() ? a->get_priority() : 0;
            int32_t pb = b.is_valid() ? b->get_priority() : 0;
            if (int32_t priority_diff = pa - pb) {
                return priority_diff > 0;
            }
            return a < b;
        }
    };

    std::map<Ref<ModifierChannel>, std::vector<std::shared_ptr<EvaluatedModifier>>, ChannelPriorityCompare> modifiers;

public:
    ModifierAggregator() { }
    ModifierAggregator(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers);

    void add_modifier(const std::shared_ptr<EvaluatedModifier>& modifier);
    void add_modifiers(const std::vector<std::shared_ptr<EvaluatedModifier>>& p_modifiers);
    bool get_modified_value(const Ref<GameplayStat>& stat, float base_value, float& out_modified_value) const;
    float get_modified_value(const Ref<GameplayStat>& stat, float base_value) const;

private:
    bool get_modified_value(const Ref<ModifierChannel>& channel, const Ref<GameplayStat>& stat, float base_value, float& out_modified_value) const;
};

#endif
