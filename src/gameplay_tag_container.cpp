#include "gameplay_tag_container.h"

void GameplayTagContainer::_bind_methods() {
    BIND_METHOD(GameplayTagContainer, add_tag, "tag")
    BIND_METHOD(GameplayTagContainer, add_tags, "tags")
    BIND_METHOD(GameplayTagContainer, remove_tag, "tag")
    BIND_METHOD(GameplayTagContainer, has_tag, "tag")
    BIND_METHOD(GameplayTagContainer, has_tag_exact, "tag")
    BIND_METHOD(GameplayTagContainer, to_array)
}

void GameplayTagContainer::add_tag(const String& tag) {
    tags.add_tag(tag);
}

void GameplayTagContainer::add_tags(const TypedArray<String>& p_tags) {
    for (size_t i = 0; i < p_tags.size(); ++i) {
        const String tag = p_tags[i];
        tags.add_tag(tag);
    }
}

bool GameplayTagContainer::remove_tag(const String& tag) {
    return tags.remove_tag(tag);
}

bool GameplayTagContainer::has_tag(const String& tag) const {
    return tags.has_tag(tag);
}

bool GameplayTagContainer::has_tag_exact(const String& tag) const {
    return tags.has_tag_exact(tag);
}

TypedArray<String> GameplayTagContainer::to_array() const {
    TypedArray<String> result;
    tags.get_string_array(result);
    return result;
}
