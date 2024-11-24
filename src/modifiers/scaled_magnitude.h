#ifndef SCALED_MAGNITUDE_H
#define SCALED_MAGNITUDE_H

#include "binding_macros.h"
#include "typedefs.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class ScaledMagnitude : public ModifierMagnitude {
    GDCLASS(ScaledMagnitude, ModifierMagnitude)

public:
    ScaledMagnitude();

    stat_value_t get_magnitude(const Ref<EffectApplicationContext>& context) const override;

    GET_SET_PROPERTY(Ref<ModifierMagnitude>, base)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, premultiply_offset)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, postmultiply_offset)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, coefficient)

protected:
    static void _bind_methods();
};

#endif
