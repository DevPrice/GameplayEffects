#ifndef STAT_BASED_MAGNITUDE_H
#define STAT_BASED_MAGNITUDE_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"
#include "stats/captured_stat.h"

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class StatBasedMagnitude : public ModifierMagnitude {
    GDCLASS(StatBasedMagnitude, ModifierMagnitude)

public:
    enum StatValueType {
        Base = 0,
        Current = 1,
        Bonus = 2,
    };

    StatBasedMagnitude();

    float get_magnitude(const EffectExecutionContext &context) override;

    GET_SET_PROPERTY(Ref<CapturedStat>, captured_stat)
    GET_SET_PROPERTY(StatValueType, value_type)

  protected:
    static void _bind_methods();
};

VARIANT_ENUM_CAST(StatBasedMagnitude::StatValueType)

#endif
