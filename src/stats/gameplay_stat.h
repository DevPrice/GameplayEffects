#ifndef GAMEPLAY_STAT_H
#define GAMEPLAY_STAT_H

#include "binding_macros.h"
#include "typedefs.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class GameplayStat : public Resource {
    GDCLASS(GameplayStat, Resource)

    GET_SET_PROPERTY(stat_value_t, base_value)

public:
    GameplayStat();

protected:
    static void _bind_methods();
};

#endif
