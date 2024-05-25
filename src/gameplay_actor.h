#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "stats/gameplay_stat.h"
#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"


#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)

public:
    virtual Ref<GameplayEffectSpec> make_effect_spec(Ref<GameplayEffect> effect);

    void apply_effect_to_self(Ref<GameplayEffect> effect);
    void apply_effect_to_target(Ref<GameplayEffect> effect, Node *target);
    void apply_effect_spec(Ref<GameplayEffectSpec> spec);

    static GameplayActor* find_actor_for_node(Node* node);

protected:
    virtual GameplayEffectContext _make_effect_context();
    EffectExecutionContext _make_execution_context(Ref<GameplayEffectSpec> &spec);

    static void _bind_methods();
};

#endif
