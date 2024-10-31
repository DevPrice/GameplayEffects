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

void GameplayTagSet::add_tag(const GameplayTag& tag) {
    tags.insert(tag);
}

bool GameplayTagSet::remove_tag(const GameplayTag& tag) {
    return tags.erase(tag);
}

bool GameplayTagSet::has_tag(const GameplayTag& tag) const {
    if (has_tag_exact(tag)) return true;
    // TODO: Use a more efficient data structure
    for (auto i = tags.begin(); i != tags.end(); ++i) {
        if (tag == *i) return true;
    }
    return false;
}

bool GameplayTagSet::has_tag_exact(const GameplayTag& tag) const {
    return tags.count(tag) > 0;
}

void GameplayTagSet::get_string_array(TypedArray<String>& array) const {
    for (auto i = tags.begin(); i != tags.end(); ++i) {
        array.push_back(i->to_string());
    }
}
