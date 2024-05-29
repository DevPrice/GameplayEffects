#ifndef CAPTURED_STAT_H
#define CAPTURED_STAT_H

#include "binding_macros.h"
#include "stats/gameplay_stat.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class CapturedStat : public Resource {
    GDCLASS(CapturedStat, Resource)

public:
    enum CaptureSource {
        Source = 0,
        Target = 2
    };

    GET_SET_PROPERTY(Ref<GameplayStat>, stat)
    GET_SET_PROPERTY(bool, snapshot)
    GET_SET_PROPERTY(CaptureSource, capture_from)

public:
    CapturedStat();

protected:
    static void _bind_methods();
};

VARIANT_ENUM_CAST(CapturedStat::CaptureSource)

#endif
