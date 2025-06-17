#ifndef EFFECT_TAGS_COMPONENT_H
#define EFFECT_TAGS_COMPONENT_H

#include "effects/effect_component.h"

#include <godot_cpp/variant/string.hpp>

class EffectTagsComponent : public EffectComponent {
    GDCLASS(EffectTagsComponent, EffectComponent)

    GET_SET_PROPERTY(PackedStringArray, effect_tags)

protected:
    static void _bind_methods();
};

#endif
