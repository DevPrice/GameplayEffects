#ifndef GRANT_TAGS_COMPONENT_H
#define GRANT_TAGS_COMPONENT_H

#include "effects/effect_component.h"

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class GrantTagsComponent : public EffectComponent {
    GDCLASS(GrantTagsComponent, EffectComponent)

    GET_SET_PROPERTY(TypedArray<String>, granted_tags)

public:
    void on_application(const Ref<EffectApplicationContext>& context) override;

protected:
    static void _bind_methods();
};

#endif