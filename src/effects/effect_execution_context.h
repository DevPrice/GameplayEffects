#ifndef EFFECT_EXECUTION_CONTEXT_H
#define EFFECT_EXECUTION_CONTEXT_H

#include "effects/gameplay_effect_spec.h"
#include "actor_snapshot.h"

#include <godot_cpp/core/object.hpp>

using namespace godot;

class GameplayActor;

struct EffectExecutionContext {
    const Ref<GameplayEffectSpec> spec = nullptr;
    const ObjectID target_actor_id;
    const ActorSnapshot target_snapshot;

    GameplayActor* get_target_actor() const;

    bool operator==(const EffectExecutionContext& other) const {
        return spec == other.spec
            && target_actor_id == other.target_actor_id
            && target_snapshot == other.target_snapshot;
    }
};

#endif
