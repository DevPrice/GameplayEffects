#include "gameplay_stat.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GameplayStat::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_base_value"), &GameplayStat::get_base_value);
    ClassDB::bind_method(D_METHOD("set_base_value", "p_base_value"), &GameplayStat::set_base_value);
    ClassDB::add_property("GameplayStat", PropertyInfo(Variant::FLOAT, "base_value"), "set_base_value", "get_base_value");
    UtilityFunctions::print("LOADED UP :)");
}

double GameplayStat::get_base_value() const {
    return base_value;
}

void GameplayStat::set_base_value(float p_base_value) {
    base_value = p_base_value;
}
