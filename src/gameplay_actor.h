#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "modifiers/evaluated_modifier.h"
#include "stats/gameplay_stat.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace godot;

struct ActiveEffect {
    const EffectExecutionContext execution_context;

    std::vector<std::shared_ptr<IEvaluatedModifier>> capture_modifier_snapshot() const;

    bool operator==(const ActiveEffect &other) const {
        return execution_context == other.execution_context;
    }
};

struct ActiveEffectHasher {
    std::size_t operator()(const ActiveEffect& active_effect) const {
        return (std::size_t)active_effect.execution_context.spec.ptr() ^ (std::size_t)active_effect.execution_context.target_actor;
    }
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

    Ref<GameplayEffectSpec> make_effect_spec(Ref<GameplayEffect> effect);

    void apply_effect_to_self(Ref<GameplayEffect> effect);
    void apply_effect_to_target(Ref<GameplayEffect> effect, Node* target);
    void apply_effect_spec(Ref<GameplayEffectSpec> spec);

    static GameplayActor* find_actor_for_node(Node* node);

protected:
    virtual Ref<GameplayEffectContext> _make_effect_context();

private:
    HashMap<Ref<GameplayStat>, StatSnapshot> stat_values;
    std::unordered_map<ActiveEffect, std::vector<std::shared_ptr<IEvaluatedModifier>>, ActiveEffectHasher> active_effects;

    EffectExecutionContext _make_execution_context(Ref<GameplayEffectSpec>& spec);
    void _execute_effect(const ActiveEffect& active_effect);
    void _recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot);

protected:
    static void _bind_methods();
};

#endif
