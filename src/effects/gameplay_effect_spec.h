#ifndef GAMEPLAY_EFFECT_SPEC_H
#define GAMEPLAY_EFFECT_SPEC_H

#include "binding_macros.h"
#include "effects/gameplay_effect.h"
#include "effects/gameplay_effect_context.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

class GameplayEffectSpec : public RefCounted {
    GDCLASS(GameplayEffectSpec, RefCounted)

    GET_SET_PROPERTY(Ref<GameplayEffect>, effect)
    GET_SET_PROPERTY(Ref<GameplayEffectContext>, context)

protected:
    static void _bind_methods();
};

#endif
