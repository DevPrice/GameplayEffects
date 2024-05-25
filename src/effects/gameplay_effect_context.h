#ifndef GAMEPLAY_EFFECT_CONTEXT_H
#define GAMEPLAY_EFFECT_CONTEXT_H

class GameplayActor;

struct GameplayEffectContext {
    const GameplayActor* source_actor = nullptr;
};

#endif
