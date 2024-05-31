#ifndef SCALED_MAGNITUDE_H
#define SCALED_MAGNITUDE_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class ScaledMagnitude : public ModifierMagnitude {
    GDCLASS(ScaledMagnitude, ModifierMagnitude)

public:
    ScaledMagnitude();

    float get_magnitude(const Ref<EffectExecutionContext>& context) override;

    GET_SET_PROPERTY(Ref<ModifierMagnitude>, base)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, premultiply_offset)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, postmultiply_offset)
    GET_SET_PROPERTY(Ref<ModifierMagnitude>, coefficient)

protected:
    static void _bind_methods();
};

#endif
