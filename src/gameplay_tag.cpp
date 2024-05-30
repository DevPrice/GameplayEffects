#include "gameplay_tag.h"

#include <godot_cpp/variant/packed_string_array.hpp>

using namespace godot;

GameplayTag::GameplayTag(const String & p_value) : value(p_value) { }

GameplayTag::GameplayTag(const GameplayTag & other) : value(other.value) { }

String GameplayTag::to_string() const {
    return value;
}

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

std::size_t GameplayTag::Hasher::operator()(const GameplayTag &tag) const {
    return tag.value.to_lower().hash();
}
