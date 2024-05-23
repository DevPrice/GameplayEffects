#ifndef GAMEPLAY_ACTOR_H
#define GAMEPLAY_ACTOR_H

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameplayActor : public Node {
    GDCLASS(GameplayActor, Node)

protected:
    static void _bind_methods();
};

#endif
