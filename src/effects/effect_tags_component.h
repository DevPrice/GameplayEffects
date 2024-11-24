#ifndef EFFECT_TAGS_COMPONENT_H
#define EFFECT_TAGS_COMPONENT_H

#include "effects/effect_component.h"

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/typed_array.hpp>

class EffectTagsComponent : public EffectComponent {
    GDCLASS(EffectTagsComponent, EffectComponent)

    GET_SET_PROPERTY(TypedArray<String>, effect_tags)

protected:
    static void _bind_methods();
};

#endif
