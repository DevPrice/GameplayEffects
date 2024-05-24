#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "../stats/gameplay_stat.h"

using namespace godot;

class StatModifier : public Resource {
    GDCLASS(StatModifier, Resource)

private:
    Ref<GameplayStat> stat;

public:
    Ref<GameplayStat> get_stat() const;
    void set_stat(const Ref<GameplayStat> p_stat);

protected:
    static void _bind_methods();
};

#endif
