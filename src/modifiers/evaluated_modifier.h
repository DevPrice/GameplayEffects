#ifndef EVALUATED_MODIFIER_H
#define EVALUATED_MODIFIER_H

#include "typedefs.h"
#include "stats/gameplay_stat.h"
#include "modifiers/modifier_channel.h"
#include "modifiers/stat_modifier.h"

#include <godot_cpp/classes/ref.hpp>

struct EvaluatedModifier {
    virtual Ref<GameplayStat> get_stat() const = 0;
    virtual StatModifier::Operation get_operation() const = 0;
    virtual stat_value_t get_magnitude() const = 0;
    virtual Ref<ModifierChannel> get_channel() const = 0;
    virtual bool requirements_met() const = 0;
};

#endif
