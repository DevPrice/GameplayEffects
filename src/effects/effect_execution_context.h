#ifndef EFFECT_EXECUTION_CONTEXT_H
#define EFFECT_EXECUTION_CONTEXT_H

#include "effects/gameplay_effect_spec.h"

class GameplayActor;

struct EffectExecutionContext {
    const Ref<GameplayEffectSpec> spec = nullptr;
    GameplayActor* const target_actor = nullptr;

    bool operator==(const EffectExecutionContext& other) const {
        return spec == other.spec && target_actor == other.target_actor;
    }
};

#endif
