#include "gameplay_tag.h"

#include <godot_cpp/variant/packed_string_array.hpp>

using namespace godot;

GameplayTag::GameplayTag(const String & p_value) : value(p_value) { }

bool GameplayTag::matches(const GameplayTag &other) const {
    auto segments = value.split(".");
    auto other_segments = other.value.split(".");

    if (segments.size() < other_segments.size()) return false;

    for (int i = 0; i < other_segments.size(); ++i) {
        if (segments[i] != other_segments[i]) return false;
    }

    return true;
}

bool GameplayTag::operator==(const GameplayTag &other) const {
    auto segments = value.split(".");
    auto other_segments = other.value.split(".");

    if (segments.size() != other_segments.size()) return false;

    for (int i = 0; i < segments.size(); ++i) {
        if (segments[i] != other_segments[i]) return false;
    }

    return true;
}
