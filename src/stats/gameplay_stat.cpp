#include "gameplay_stat.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GameplayStat::_bind_methods() {
    BIND_GET_SET(GameplayStat, base_value, Variant::FLOAT)
}

GET_SET_PROPERTY_IMPL(GameplayStat, double, base_value)
