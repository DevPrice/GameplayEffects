#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "typedefs.h"
#include "actor_snapshot.h"
#include "gameplay_tag_container.h"
#include "effects/effect_execution_context.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "modifiers/evaluated_modifier.h"
#include "stats/gameplay_stat.h"

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

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)
    GET_SET_OBJECT_PTR(Node, avatar)

public:
    GameplayActor();

    Ref<GameplayTagContainer> get_tags() const;

    StatSnapshot get_stat_snapshot(const Ref<GameplayStat>& stat) const;
    stat_value_t get_stat_base_value(const Ref<GameplayStat>& stat) const;
    stat_value_t get_stat_current_value(const Ref<GameplayStat>& stat) const;
    void set_stat_base_value(const Ref<GameplayStat>& stat, stat_value_t base_value);

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
    Ref<GameplayTagContainer> tag_container;

    Ref<GameplayEffectContext> _make_effect_context();
    Ref<EffectExecutionContext> _make_execution_context(const Ref<GameplayEffectSpec>& spec);
    void _execute_effect(const ActiveEffect& active_effect);
    void _recalculate_stats();
    void _recalculate_stats(const HashMap<Ref<GameplayStat>, StatSnapshot>& stat_snapshot);
    bool _remove_effect(const ActiveEffect& active_effect);

    static String& get_actor_meta_name();

protected:
    static void _bind_methods();

    GDVIRTUAL0RC(Variant, _get_custom_context_data)
};

#endif
