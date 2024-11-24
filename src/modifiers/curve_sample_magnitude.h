#ifndef CURVE_SAMPLE_MAGNITUDE_H
#define CURVE_SAMPLE_MAGNITUDE_H

#include "binding_macros.h"
#include "typedefs.h"
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

    stat_value_t get_magnitude(const Ref<EffectApplicationContext>& context) const override;

  protected:
    static void _bind_methods();
};

#endif
