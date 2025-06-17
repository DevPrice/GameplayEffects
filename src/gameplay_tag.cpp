#include "gameplay_tag.h"

#include <algorithm>
#include <iterator>
#include <godot_cpp/variant/packed_string_array.hpp>

using namespace godot;

std::vector<StringName> GameplayTag::make_parts(const String& tag) {
    const PackedStringArray raw_parts = tag.split(".", false);
    std::vector<StringName> parts;
    parts.reserve(raw_parts.size());
    for (int i = 0; i < raw_parts.size(); ++i) {
        const String& part = raw_parts[i];
        parts.emplace_back(part.strip_edges().to_lower().to_snake_case());
    }
    return parts;
}

GameplayTag::GameplayTag(const String& p_value) : value(p_value), normalized_parts(make_parts(p_value)) {}

GameplayTag::GameplayTag(const GameplayTag& other) : value(other.value), normalized_parts(other.normalized_parts) {}

String GameplayTag::to_string() const {
    return value;
}

bool GameplayTag::matches(const GameplayTag &other) const {
    if (normalized_parts.size() < other.normalized_parts.size()) return false;

    for (int i = 0; i < other.normalized_parts.size(); ++i) {
        if (normalized_parts[i] != other.normalized_parts[i]) return false;
    }

    return true;
}

bool GameplayTag::operator==(const GameplayTag &other) const {
    if (normalized_parts.size() != other.normalized_parts.size()) return false;

    for (int i = 0; i < normalized_parts.size(); ++i) {
        if (normalized_parts[i] != other.normalized_parts[i]) return false;
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

void GameplayTagSet::to_string_array(PackedStringArray& out_array) const {
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
