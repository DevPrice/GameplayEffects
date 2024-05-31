#ifndef EFFECT_EXECUTION_CONTEXT_H
#define EFFECT_EXECUTION_CONTEXT_H

#include "effects/gameplay_effect_spec.h"
#include "actor_snapshot.h"

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <memory>

using namespace godot;

class GameplayActor;

struct EffectExecutionContext : public RefCounted {
    GDCLASS(EffectExecutionContext, RefCounted)

    GET_SET_PROPERTY(Ref<GameplayEffectSpec>, spec)
    GET_SET_OBJECT_PTR(GameplayActor, target_actor)

private:
    std::unique_ptr<ActorSnapshot> target_snapshot;

public:
    ActorSnapshot get_target_snapshot() const;
    void set_target_snapshot(const ActorSnapshot& p_target_snapshot);

    bool operator==(const EffectExecutionContext& other) const;

protected:
    static void _bind_methods();
};

#endif
