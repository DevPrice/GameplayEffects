#ifndef GAMEPLAY_EFFECT_SPEC_H
#define GAMEPLAY_EFFECT_SPEC_H

#include "binding_macros.h"
#include "effects/gameplay_effect.h"
#include "effects/effect_execution_context.h"

#include <memory>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class GameplayEffectSpec : public RefCounted {
    GDCLASS(GameplayEffectSpec, RefCounted)

    GET_SET_PROPERTY(Ref<GameplayEffect>, effect)
    GET_SET_PROPERTY(EffectExecutionContext, execution_context)

protected:
    static void _bind_methods();
};

#endif
