#include "gameplay_stat.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayStat::_bind_methods(){
    BIND_GET_SET(GameplayStat, base_value, Variant::FLOAT)
}

GameplayStat::GameplayStat() {
    base_value = stat_value_t{};
}

GET_SET_PROPERTY_IMPL(GameplayStat, stat_value_t, base_value)
