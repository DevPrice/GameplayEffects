#include "gameplay_actor.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GameplayActor::_bind_methods() {
    BIND_GET_SET_RESOURCE_ARRAY(GameplayActor, stats, GameplayStat)
}

GET_SET_PROPERTY_IMPL(GameplayActor, TypedArray<GameplayStat>, stats)
