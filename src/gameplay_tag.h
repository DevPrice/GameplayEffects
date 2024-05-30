#ifndef GAMEPLAY_TAG_H
#define GAMEPLAY_TAG_H

#include <godot_cpp/variant/string.hpp>

using namespace godot;

struct GameplayTag {

    const String value;

    GameplayTag(const String& p_value);

    bool matches(const GameplayTag& other) const;

    bool operator==(const GameplayTag& other) const;
};

#endif
