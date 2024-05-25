#ifndef EFFECT_EXECUTION_CONTEXT_H
#define EFFECT_EXECUTION_CONTEXT_H

#include "effects/gameplay_effect_spec.h"

class GameplayActor;

struct EffectExecutionContext {
    Ref<GameplayEffectSpec> effect;
    GameplayActor* target_actor = nullptr;
};

#endif
