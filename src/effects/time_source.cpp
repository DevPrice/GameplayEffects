#include "effects/time_source.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void TimeSource::_bind_methods() {

}

void EffectTimer::_bind_methods() {
   
}

void EffectTimer::set_callback(std::function<void()> p_callback) {
    callback = p_callback;
}
