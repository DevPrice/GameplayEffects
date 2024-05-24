#include "modifiers/stat_modifier.h"
#include "godot_cpp/classes/global_constants.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void StatModifier::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_stat"), &StatModifier::get_stat);
    ClassDB::bind_method(D_METHOD("set_stat", "p_stat"), &StatModifier::set_stat);
    ClassDB::add_property("StatModifier", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "GameplayStat"), "set_stat", "get_stat");
}

Ref<GameplayStat> StatModifier::get_stat() const {
    return stat;
}

void StatModifier::set_stat(const Ref<GameplayStat> p_stat) {
    stat = p_stat;
}
