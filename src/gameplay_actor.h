#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include "stats/gameplay_stat.h"

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

    GET_SET_PROPERTY(TypedArray<GameplayStat>, stats)

protected:
    static void _bind_methods();
};

#endif
