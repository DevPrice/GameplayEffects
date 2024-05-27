#ifndef MODIFIER_AGGREGATOR_H
#define MODIFIER_AGGREGATOR_H

#include "stats/gameplay_stat.h"

#include <vector>
#include <memory>
#include <godot_cpp/classes/ref.hpp>

class IEvaluatedModifier;

using namespace godot;

struct ModifierAggregator {
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifiers;

    bool get_modified_value(const Ref<GameplayStat>& stat, float baseValue, float& modifiedValue) const;
    float get_modified_value(const Ref<GameplayStat>& stat, float baseValue) const;
};

#endif
