#ifndef EFFECT_EXECUTION_CONTEXT_H
#define EFFECT_EXECUTION_CONTEXT_H

#include "effects/gameplay_effect_spec.h"
#include "actor_snapshot.h"

class GameplayActor;

struct EffectExecutionContext {
    const Ref<GameplayEffectSpec> spec = nullptr;
    GameplayActor* const target_actor = nullptr;
    const ActorSnapshot target_snapshot;

    bool operator==(const EffectExecutionContext& other) const {
        return spec == other.spec
            && target_actor == other.target_actor
            && target_snapshot == other.target_snapshot;
    }
};

#endif
