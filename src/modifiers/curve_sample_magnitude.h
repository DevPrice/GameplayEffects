#ifndef CURVE_SAMPLE_MAGNITUDE_H
#define CURVE_SAMPLE_MAGNITUDE_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"

#include <godot_cpp/classes/curve.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class CurveSampleMagnitude : public ModifierMagnitude {
    GDCLASS(CurveSampleMagnitude, ModifierMagnitude)

    GET_SET_PROPERTY(Ref<ModifierMagnitude>, offset)
    GET_SET_PROPERTY(Ref<Curve>, curve)

public:
    CurveSampleMagnitude();

    float get_magnitude(const EffectExecutionContext& context) override;

  protected:
    static void _bind_methods();
};

#endif
