#ifndef GAMEPLAY_STAT_H
#define GAMEPLAY_STAT_H

#include "binding_macros.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class GameplayStat : public Resource {
    GDCLASS(GameplayStat, Resource)

    GET_SET_PROPERTY(double, base_value)

public:
    GameplayStat();

protected:
    static void _bind_methods();
};

#endif
