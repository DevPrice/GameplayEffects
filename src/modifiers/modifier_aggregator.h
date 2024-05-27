#ifndef MODIFIER_AGGREGATOR_H
#define MODIFIER_AGGREGATOR_H

#include "modifiers/evaluated_modifier.h"
#include "stats/gameplay_stat.h"

#include <vector>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

struct ModifierAggregator {
    std::vector<IEvaluatedModifier*> modifiers;

    bool get_modified_value(const Ref<GameplayStat>& stat, float baseValue, float& modifiedValue) const;
    float get_modified_value(const Ref<GameplayStat>& stat, float baseValue) const;
};

#endif
