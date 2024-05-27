#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "stats/gameplay_stat.h"
#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "modifiers/modifier_aggregator.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>

using namespace godot;

struct ActiveEffect {
    const Ref<GameplayEffectSpec> spec = nullptr;
    const GameplayActor *target = nullptr;
    const EffectExecutionContext execution_context;
};

struct StatSnapshot {
    float base_value = 0.f;
    float current_value = 0.f;
};

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)

public:
    StatSnapshot get_stat_snapshot(const Ref<GameplayStat>& stat) const;
    float get_stat_base_value(Ref<GameplayStat> stat) const;
    float get_stat_current_value(Ref<GameplayStat> stat) const;

    virtual Ref<GameplayEffectSpec> make_effect_spec(Ref<GameplayEffect> effect);

    void apply_effect_to_self(Ref<GameplayEffect> effect);
    void apply_effect_to_target(Ref<GameplayEffect> effect, Node* target);
    void apply_effect_spec(Ref<GameplayEffectSpec> spec);

    static GameplayActor* find_actor_for_node(Node* node);

protected:
    virtual GameplayEffectContext _make_effect_context();
    EffectExecutionContext _make_execution_context(Ref<GameplayEffectSpec>& spec);

private:
    HashMap<Ref<GameplayStat>, StatSnapshot> stat_values;

    void execute_effect(const ActiveEffect& active_effect);

protected:
    static void _bind_methods();
};

#endif
