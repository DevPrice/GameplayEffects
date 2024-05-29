#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "actor_snapshot.h"
#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "modifiers/evaluated_modifier.h"
#include "stats/gameplay_stat.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace godot;

struct ActiveEffect {
    const EffectExecutionContext execution_context;

    std::vector<std::shared_ptr<IEvaluatedModifier>> capture_modifier_snapshot() const;

    ActiveEffect(const EffectExecutionContext& p_execution_context) : execution_context(p_execution_context) { }

    bool operator==(const ActiveEffect &other) const {
        return execution_context == other.execution_context;
    }

    struct Hasher {
        std::size_t operator()(const ActiveEffect& active_effect) const {
            return (std::size_t)active_effect.execution_context.spec.ptr() ^ (std::size_t)active_effect.execution_context.target_actor;
        }
    };
};

class ActiveEffectHandle : public RefCounted {
    GDCLASS(ActiveEffectHandle, RefCounted)

private:
    std::unique_ptr<ActiveEffect> active_effect;

public:
    std::unique_ptr<ActiveEffect> get_active_effect() const;
    void set_active_effect(const ActiveEffect& active_effect);

protected:
    static void _bind_methods();
};

struct ActiveEffectState {
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifiers;
    Ref<EffectTimer> period;
    Ref<EffectTimer> duration;
};

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)

public:
    StatSnapshot get_stat_snapshot(const Ref<GameplayStat>& stat) const;
    float get_stat_base_value(Ref<GameplayStat> stat) const;
    float get_stat_current_value(Ref<GameplayStat> stat) const;

    ActorSnapshot capture_snapshot() const;

    Ref<GameplayEffectSpec> make_effect_spec(Ref<GameplayEffect> effect);

    Ref<ActiveEffectHandle> apply_effect_to_self(Ref<GameplayEffect> effect);
    Ref<ActiveEffectHandle> apply_effect_to_target(Ref<GameplayEffect> effect, Node* target);
    Ref<ActiveEffectHandle> apply_effect_spec(Ref<GameplayEffectSpec> spec);
    bool remove_effect(Ref<ActiveEffectHandle> handle);

    static GameplayActor* find_actor_for_node(Node* node);

private:
    HashMap<Ref<GameplayStat>, StatSnapshot> stat_values;
    std::unordered_map<ActiveEffect, ActiveEffectState, ActiveEffect::Hasher> active_effects;

    Ref<GameplayEffectContext> _make_effect_context();
    EffectExecutionContext _make_execution_context(Ref<GameplayEffectSpec>& spec);
    void _execute_effect(const ActiveEffect& active_effect);
    void _recalculate_stats();
    void _recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot);
    bool _remove_effect(const ActiveEffect &active_effect);

  protected:
    static void _bind_methods();
};

#endif
