#include "binding_macros.h"
#include "effect_tags_component.h"

void EffectTagsComponent::_bind_methods() {
    BIND_GET_SET_STRING_ARRAY(EffectTagsComponent, effect_tags);
}

GET_SET_PROPERTY_IMPL(EffectTagsComponent, TypedArray<String>, effect_tags)
