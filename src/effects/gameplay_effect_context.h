#ifndef GAMEPLAY_EFFECT_CONTEXT_H
#define GAMEPLAY_EFFECT_CONTEXT_H

#include "binding_macros.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

class GameplayActor;

using namespace godot;

class GameplayEffectContext : public RefCounted {
    GDCLASS(GameplayEffectContext, RefCounted)

    GET_SET_PROPERTY(GameplayActor*, source_actor)

protected:
    static void _bind_methods();
};

#endif
