#ifndef TIME_SOURCE_H
#define TIME_SOURCE_H

#include "binding_macros.h"

#include <godot_cpp/classes/resource.hpp>

class EffectExecutionContext;

using namespace godot;

struct IEffectTimer {
    virtual void stop() = 0;
};

class TimeSource : public Resource {
    GDCLASS(TimeSource, Resource)

public:
    virtual IEffectTimer create_timer(const EffectExecutionContext& execution_context) const = 0;
    virtual IEffectTimer create_interval(const EffectExecutionContext& execution_context) const = 0;

protected:
    static void _bind_methods();
};

#endif
