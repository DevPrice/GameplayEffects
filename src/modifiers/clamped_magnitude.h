#ifndef CLAMPED_MAGNITUDE_H
#define CLAMPED_MAGNITUDE_H

#include "binding_macros.h"
#include "typedefs.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class ClampedMagnitude : public ModifierMagnitude {
    GDCLASS(ClampedMagnitude, ModifierMagnitude)

public:
    ClampedMagnitude();

    stat_value_t get_magnitude(const Ref<EffectExecutionContext>& context) override;

    GET_SET_PROPERTY(Ref<ModifierMagnitude>, value)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, min_value)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, max_value)

protected:
    static void _bind_methods();
};

#endif
