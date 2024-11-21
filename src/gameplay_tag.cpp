#include "gameplay_tag.h"

#include <algorithm>
#include <iterator>
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

bool GameplayTag::operator<(const GameplayTag& other) const {
    return value < other.value;
}

std::size_t GameplayTag::Hasher::operator()(const GameplayTag &tag) const {
    return tag.value.to_lower().hash();
}

GameplayTagSet::GameplayTagSet(const std::unordered_set<GameplayTag, GameplayTag::Hasher>& p_tags) {
    tags.insert(p_tags.begin(), p_tags.end());
}

bool GameplayTagSet::add_tag(const GameplayTag& tag) {
    auto [_, added] = tags.insert(tag);
    return added;
}

bool GameplayTagSet::remove_tag(const GameplayTag& tag) {
    return tags.erase(tag);
}

void GameplayTagSet::clear() {
    tags.clear();
}

bool GameplayTagSet::has_tag(const GameplayTag& tag) const {
    if (has_tag_exact(tag)) return true;
    // TODO: Use a more efficient data structure
    return std::any_of(tags.begin(), tags.end(), [&tag](const GameplayTag& element) -> bool {
        return element.matches(tag);
    });
}

bool GameplayTagSet::has_tag_exact(const GameplayTag& tag) const {
    return tags.count(tag) > 0;
}

bool GameplayTagSet::is_empty() const {
    return tags.size() == 0;
}

void GameplayTagSet::to_string_array(TypedArray<String>& out_array) const {
    for (auto i = tags.begin(); i != tags.end(); ++i) {
        out_array.push_back(i->to_string());
    }
}

void GameplayTagSet::to_set(std::unordered_set<GameplayTag, GameplayTag::Hasher>& out_tags) const {
    out_tags.insert(tags.begin(), tags.end());
}

GameplayTagSet GameplayTagSet::operator+(const GameplayTagSet& other) const {
    GameplayTagSet result(tags);
    result += other;
    return result;
}

GameplayTagSet GameplayTagSet::operator-(const GameplayTagSet& other) const {
    std::unordered_set<GameplayTag, GameplayTag::Hasher> difference;
    std::set_difference(tags.begin(), tags.end(), other.tags.begin(), other.tags.end(), std::inserter(difference, difference.begin()));
    return GameplayTagSet(difference);
}

GameplayTagSet& GameplayTagSet::operator+=(const GameplayTagSet& other) {
    tags.insert(other.tags.begin(), other.tags.end());
    return *this;
}

GameplayTagSet& GameplayTagSet::operator-=(const GameplayTagSet& other) {
    tags.erase(other.tags.begin(), other.tags.end());
    return *this;
}
