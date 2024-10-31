#ifndef GAMEPLAY_TAG_CONTAINER_H
#define GAMEPLAY_TAG_CONTAINER_H

#include "binding_macros.h"
#include "gameplay_tag.h"
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

class GameplayTagContainer : public RefCounted {
    GDCLASS(GameplayTagContainer, RefCounted)

public:
    void add_tag(const String& tag);
    void add_tags(const TypedArray<String>& p_tags);
    void append(const GameplayTagContainer* other);
    bool remove_tag(const String& tag);
    void remove_tags(const TypedArray<String>& p_tags);
    void clear();

    bool has_tag(const String& tag) const;
    bool has_tag_exact(const String& tag) const;

    TypedArray<String> to_array() const;

private:
    GameplayTagSet tags;

protected:
    static void _bind_methods();
};

#endif