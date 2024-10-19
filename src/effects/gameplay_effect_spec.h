#ifndef GAMEPLAY_EFFECT_SPEC_H
#define GAMEPLAY_EFFECT_SPEC_H

#include "binding_macros.h"
#include "effects/gameplay_effect.h"
#include "effects/gameplay_effect_context.h"
#include "gameplay_tag.h"
#include "typedefs.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <unordered_map>

using namespace godot;

class GameplayEffectSpec : public RefCounted {
    GDCLASS(GameplayEffectSpec, RefCounted)

    GET_SET_PROPERTY(Ref<GameplayEffect>, effect)
    GET_SET_PROPERTY(Ref<GameplayEffectContext>, context)

public:
    Ref<GameplayEffectSpec> with_tag_magnitude(const String& tag, stat_value_t magnitude) const;
    Ref<GameplayEffectSpec> with_tag_magnitudes(const Dictionary& p_tag_magnitudes) const;

    bool get_tag_magnitude(const GameplayTag& tag, stat_value_t& out_magnitude) const;
    void set_tag_magnitude(const GameplayTag& tag, stat_value_t magnitude);
    void set_tag_magnitudes(const std::unordered_map<GameplayTag, stat_value_t, GameplayTag::Hasher>& p_tag_magnitudes);
    void add_tag_magnitudes(const Dictionary& p_tag_magnitudes);

  private:
    std::unordered_map<GameplayTag, stat_value_t, GameplayTag::Hasher> tag_magnitudes;

protected:
    static void _bind_methods();
};

#endif
