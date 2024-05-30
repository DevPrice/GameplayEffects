#ifndef GAMEPLAY_TAG_H
#define GAMEPLAY_TAG_H

#include <godot_cpp/variant/string.hpp>

using namespace godot;

class GameplayTag {

private:
    String value;

public:
    GameplayTag(const String& p_value);
    GameplayTag(const GameplayTag& other);

    String to_string() const;
    bool matches(const GameplayTag& other) const;

    bool operator==(const GameplayTag& other) const;

    struct Hasher {
        std::size_t operator()(const GameplayTag& tag) const;
    };
};

#endif
