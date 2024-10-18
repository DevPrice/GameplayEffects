#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "actor_snapshot.h"
#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "modifiers/evaluated_modifier.h"
#include "stats/gameplay_stat.h"
#include "stats/stat_component.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace godot;

struct ActiveEffect {
    const Ref<EffectExecutionContext> execution_context;

    std::vector<std::shared_ptr<EvaluatedModifier>> capture_modifier_snapshot() const;

    ActiveEffect(const Ref<EffectExecutionContext>& p_execution_context) : execution_context(p_execution_context) { }

    bool operator==(const ActiveEffect &other) const {
        return *execution_context == *other.execution_context;
    }

    struct Hasher {
        std::size_t operator()(const ActiveEffect& active_effect) const {
            return (std::size_t)active_effect.execution_context->get_spec().ptr() ^ (std::size_t)active_effect.execution_context->get_target_actor();
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

    Ref<GameplayEffectSpec> get_spec() const;

protected:
    static void _bind_methods();
};

struct ActiveEffectState {
    std::vector<std::shared_ptr<EvaluatedModifier>> modifiers;
    Ref<EffectTimer> period;
    Ref<EffectTimer> duration;
};

/**
 * This exists only because Godot doesn't support instantiating virtual types directly.
 */
class BaseGameplayActor : public Node {
    GDCLASS(BaseGameplayActor, Node)

protected:
    static void _bind_methods();

    GDVIRTUAL0RC(Variant, _get_custom_context_data)
};

class GameplayActor : public BaseGameplayActor {
    GDCLASS(GameplayActor, BaseGameplayActor)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)
    GET_SET_PROPERTY(TypedArray<StatComponent>, stat_components)
    GET_SET_OBJECT_PTR(Node, avatar)

public:
    StatSnapshot get_stat_snapshot(const Ref<GameplayStat>& stat) const;
    float get_stat_base_value(const Ref<GameplayStat>& stat) const;
    float get_stat_current_value(const Ref<GameplayStat>& stat) const;
    void set_stat_base_value(const Ref<GameplayStat>& stat, float base_value);

    ActorSnapshot capture_snapshot() const;

    Ref<GameplayEffectSpec> make_effect_spec(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes = Dictionary());

    Ref<ActiveEffectHandle> apply_effect_to_self(const Ref<GameplayEffect>& effect, const Dictionary& tag_magnitudes = Dictionary());
    Ref<ActiveEffectHandle> apply_effect_to_target(const Ref<GameplayEffect>& effect, Node* target, const Dictionary& tag_magnitudes = Dictionary());
    Ref<ActiveEffectHandle> apply_effect_spec(const Ref<GameplayEffectSpec>& spec);
    bool remove_effect(const Ref<ActiveEffectHandle>& handle);

    static GameplayActor* find_actor_for_node(Node* node);
    static void set_owning_actor(Node* node, GameplayActor* actor);

private:
    HashMap<Ref<GameplayStat>, StatSnapshot> stat_values;
    std::unordered_map<ActiveEffect, ActiveEffectState, ActiveEffect::Hasher> active_effects;

    Ref<GameplayEffectContext> _make_effect_context();
    Ref<EffectExecutionContext> _make_execution_context(const Ref<GameplayEffectSpec>& spec);
    void _execute_effect(const ActiveEffect& active_effect);
    void _recalculate_stats();
    void _recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot);
    bool _remove_effect(const ActiveEffect& active_effect);

    static String& get_actor_meta_name();

protected:
    static void _bind_methods();
};

#endif
