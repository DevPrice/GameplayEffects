#include "effects/gameplay_effect_spec.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include "gameplay_effect_spec.h"

using namespace godot;

void GameplayEffectSpec::_bind_methods() {
    BIND_METHOD(GameplayEffectSpec, get_effect)
    BIND_METHOD(GameplayEffectSpec, get_context)
    BIND_METHOD(GameplayEffectSpec, with_tag_magnitude, "tag", "magnitude")
    BIND_METHOD(GameplayEffectSpec, with_tag_magnitudes, "tag_magnitudes")
}

Ref<GameplayEffectSpec> GameplayEffectSpec::with_tag_magnitude(const String& tag, stat_value_t magnitude) const {
    Ref<GameplayEffectSpec> new_spec;
    new_spec.instantiate();
    new_spec->set_effect(effect);
    new_spec->set_context(context);
    new_spec->set_tag_magnitudes(tag_magnitudes);
    new_spec->set_tag_magnitude(tag, magnitude);
    return new_spec;
}

Ref<GameplayEffectSpec> GameplayEffectSpec::with_tag_magnitudes(const Dictionary& p_tag_magnitudes) const {
    Ref<GameplayEffectSpec> new_spec;
    new_spec.instantiate();
    new_spec->set_effect(effect);
    new_spec->set_context(context);
    new_spec->set_tag_magnitudes(tag_magnitudes);
    new_spec->add_tag_magnitudes(p_tag_magnitudes);

    return new_spec;
}

bool GameplayEffectSpec::get_tag_magnitude(const GameplayTag& tag, stat_value_t& out_magnitude) const {
    if (tag_magnitudes.count(tag)) {
        out_magnitude = tag_magnitudes.at(tag);
        return true;
    }
    return false;
}

void GameplayEffectSpec::set_tag_magnitude(const GameplayTag& tag, stat_value_t magnitude) {
    tag_magnitudes[tag] = magnitude;
}

void GameplayEffectSpec::set_tag_magnitudes(const std::unordered_map<GameplayTag, stat_value_t, GameplayTag::Hasher>& p_tag_magnitudes) {
    tag_magnitudes = p_tag_magnitudes;
}

void GameplayEffectSpec::add_tag_magnitudes(const Dictionary & p_tag_magnitudes) {
    Array tags = p_tag_magnitudes.keys();
    for (int i = 0; i < tags.size(); ++i) {
        Variant& key = tags[i];
        const GameplayTag tag(key.stringify());
        const stat_value_t magnitude = p_tag_magnitudes.get(key, stat_value_t{});
        set_tag_magnitude(tag, magnitude);
    }
}

GET_SET_PROPERTY_IMPL(GameplayEffectSpec, Ref<GameplayEffect>, effect)
GET_SET_PROPERTY_IMPL(GameplayEffectSpec, Ref<GameplayEffectContext>, context)
