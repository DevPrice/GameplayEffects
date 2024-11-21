#ifndef GAMEPLAY_TAG_H
#define GAMEPLAY_TAG_H

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <unordered_set>

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
    bool operator<(const GameplayTag& other) const;

    struct Hasher {
        std::size_t operator()(const GameplayTag& tag) const;
    };
};

class GameplayTagSet {

public:
    GameplayTagSet() = default;
    explicit GameplayTagSet(const std::unordered_set<GameplayTag, GameplayTag::Hasher>& p_tags);

    bool add_tag(const GameplayTag& tag);
    template<typename _InputIterator>
    void add_tags(_InputIterator first, _InputIterator last) { tags.insert(first, last); }
    bool remove_tag(const GameplayTag& tag);
    void clear();

    bool has_tag(const GameplayTag& tag) const;
    bool has_tag_exact(const GameplayTag& tag) const;
    bool is_empty() const;

    void to_string_array(TypedArray<String>& out_array) const;
    void to_set(std::unordered_set<GameplayTag, GameplayTag::Hasher>& out_tags) const;

    GameplayTagSet operator+(const GameplayTagSet& other) const;
    GameplayTagSet operator-(const GameplayTagSet& other) const;
    GameplayTagSet& operator+=(const GameplayTagSet& other);
    GameplayTagSet& operator-=(const GameplayTagSet& other);

private:
    std::unordered_set<GameplayTag, GameplayTag::Hasher> tags;
};

#endif
