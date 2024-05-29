#include "stats/captured_stat.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void CapturedStat::_bind_methods() {
    BIND_ENUM_CONSTANT(Source)
    BIND_ENUM_CONSTANT(Target)
    BIND_GET_SET_ENUM(CapturedStat, capture_from, "Source:0,Target:1")
    BIND_GET_SET_RESOURCE(CapturedStat, stat, GameplayStat)
}

CapturedStat::CapturedStat() : snapshot(false), capture_from(Source) { }

GET_SET_PROPERTY_IMPL(CapturedStat, Ref<GameplayStat>, stat)
GET_SET_PROPERTY_IMPL(CapturedStat, bool, snapshot)
GET_SET_PROPERTY_IMPL(CapturedStat, CapturedStat::CaptureSource, capture_from)
