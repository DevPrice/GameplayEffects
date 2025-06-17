#include "gameplay_tag_container.h"

#include <algorithm>

void GameplayTagContainer::_bind_methods() {
    BIND_METHOD(GameplayTagContainer, add_tag, "tag")
    BIND_METHOD(GameplayTagContainer, add_tags, "tags")
    BIND_METHOD(GameplayTagContainer, append, "other")
    BIND_METHOD(GameplayTagContainer, remove_tag, "tag")
    BIND_METHOD(GameplayTagContainer, remove_tags, "tags")
    BIND_METHOD(GameplayTagContainer, clear)
    BIND_METHOD(GameplayTagContainer, has_tag, "tag")
    BIND_METHOD(GameplayTagContainer, has_tag_exact, "tag")
    BIND_METHOD(GameplayTagContainer, to_array)
    ADD_SIGNAL(MethodInfo("tags_changed",
        PropertyInfo(Variant::PACKED_STRING_ARRAY, "added_tags"),
        PropertyInfo(Variant::PACKED_STRING_ARRAY, "removed_tags")));
}

void GameplayTagContainer::add_tag(const String& tag) {
    if (tags.add_tag(tag)) {
        PackedStringArray added_tags;
        added_tags.append(tag);
        emit_signal("tags_changed", added_tags, PackedStringArray());
    }
}

void GameplayTagContainer::add_tags(const PackedStringArray& p_tags) {
    PackedStringArray added_tags;
    for (size_t i = 0; i < p_tags.size(); ++i) {
        const String tag = p_tags[i];
        if (!tags.has_tag_exact(tag)) {
            tags.add_tag(tag);
            added_tags.append(tag);
        }
    }
    if (added_tags.size() > 0) {
        emit_signal("tags_changed", added_tags, PackedStringArray());
    }
}

void GameplayTagContainer::append(const GameplayTagContainer* other) {
    if (other) {
        const GameplayTagSet difference = other->tags - tags;
        PackedStringArray added_tags;
        difference.to_string_array(added_tags);
        tags += other->tags;
        if (added_tags.size() > 0) {
            emit_signal("tags_changed", added_tags, PackedStringArray());
        }
    }
}

bool GameplayTagContainer::remove_tag(const String& tag) {
    if (tags.remove_tag(tag)) {
        PackedStringArray removed_tags;
        removed_tags.append(tag);
        emit_signal("tags_changed", PackedStringArray(), removed_tags);
        return true;
    }
    return false;
}

void GameplayTagContainer::remove_tags(const PackedStringArray& p_tags) {
    PackedStringArray removed_tags;
    for (size_t i = 0; i < p_tags.size(); ++i) {
        const String tag = p_tags[i];
        if (tags.remove_tag(tag)) {
            removed_tags.append(tag);
        }
    }
    if (removed_tags.size() > 0) {
        emit_signal("tags_changed", PackedStringArray(), removed_tags);
    }
}

void GameplayTagContainer::clear() {
    if (!tags.is_empty()) {
        PackedStringArray removed_tags;
        tags.to_string_array(removed_tags);
        tags.clear();
        emit_signal("tags_changed", PackedStringArray(), removed_tags);
    }
}

bool GameplayTagContainer::has_tag(const String& tag) const {
    return tags.has_tag(tag);
}

bool GameplayTagContainer::has_tag_exact(const String& tag) const {
    return tags.has_tag_exact(tag);
}

PackedStringArray GameplayTagContainer::to_array() const {
    PackedStringArray result;
    tags.to_string_array(result);
    return result;
}

GameplayTagSet GameplayTagContainer::to_tag_set() const {
    return tags;
}
