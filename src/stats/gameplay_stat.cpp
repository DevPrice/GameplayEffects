#include "gameplay_stat.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayStat::_bind_methods(){
    BIND_GET_SET(GameplayStat, base_value, Variant::FLOAT)
}

GameplayStat::GameplayStat() {
    base_value = 0.f;
}

GET_SET_PROPERTY_IMPL(GameplayStat, float, base_value)
