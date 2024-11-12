#ifndef GAMEPLAY_EFFECT_CONTEXT_H
#define GAMEPLAY_EFFECT_CONTEXT_H

#include "actor_snapshot.h"
#include "binding_macros.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <memory>

class GameplayActor;

using namespace godot;

class GameplayEffectContext : public RefCounted {
    GDCLASS(GameplayEffectContext, RefCounted)

    GET_SET_OBJECT_PTR(GameplayActor, source_actor)
    GET_SET_PROPERTY(Variant, custom_data)

private:
    std::shared_ptr<ActorSnapshot> source_snapshot;

public:
    std::shared_ptr<ActorSnapshot> get_source_snapshot() const;
    void set_source_snapshot(const ActorSnapshot& actor_snapshot);

protected:
    static void _bind_methods();
};

#endif
