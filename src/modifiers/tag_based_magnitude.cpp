#include "tag_based_magnitude.h"
#include "effects/effect_execution_context.h"

void TagBasedMagnitude::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_tag"), &TagBasedMagnitude::get_tag_value);
    ClassDB::bind_method(D_METHOD("set_tag", "p_tag"), &TagBasedMagnitude::set_tag_value);
    ClassDB::add_property(get_class_static(), PropertyInfo(Variant::STRING, "tag"), "set_tag", "get_tag");;
}

TagBasedMagnitude::TagBasedMagnitude() : tag(GameplayTag("")) { }

stat_value_t TagBasedMagnitude::get_magnitude(const Ref<EffectExecutionContext>& context) {
    stat_value_t magnitude{};
    if (context->get_spec().is_valid() && context->get_spec().is_valid() && context->get_spec()->get_tag_magnitude(tag, magnitude)) {
        return magnitude;
    }
    return 0.0f;
}

String TagBasedMagnitude::get_tag_value() const {
    return tag.to_string();
}

void TagBasedMagnitude::set_tag_value(const String& p_tag) {
    tag = GameplayTag(p_tag);
}

GameplayTag TagBasedMagnitude::get_tag() const {
    return tag;
}

void TagBasedMagnitude::set_tag(const GameplayTag& p_tag) {
    tag = p_tag;
}
