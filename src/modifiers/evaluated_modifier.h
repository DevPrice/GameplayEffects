#ifndef EVALUATED_MODIFIER_H
#define EVALUATED_MODIFIER_H

#include "stats/gameplay_stat.h"
#include "modifiers/stat_modifier.h"

#include <godot_cpp/classes/ref.hpp>

struct EvaluatedModifier {
    virtual Ref<GameplayStat> get_stat() const = 0;
    virtual StatModifier::Operation get_operation() const = 0;
    virtual float get_magnitude() const = 0;
    virtual bool requirements_met() const = 0;
};

#endif
