#ifndef TAG_BASED_MAGNITUDE_H
#define TAG_BASED_MAGNITUDE_H

#include "binding_macros.h"
#include "modifiers/modifier_magnitude.h"
#include "gameplay_tag.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

class TagBasedMagnitude : public ModifierMagnitude {
    GDCLASS(TagBasedMagnitude, ModifierMagnitude)

public:
    TagBasedMagnitude();

    float get_magnitude(const Ref<EffectExecutionContext>& context) override;

    String get_tag_value() const;
    void set_tag_value(const String& p_tag);
    GameplayTag get_tag() const;
    void set_tag(const GameplayTag& p_tag);

protected:
    static void _bind_methods();

private:
    GameplayTag tag;
};

#endif
