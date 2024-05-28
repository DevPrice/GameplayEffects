#ifndef TIME_SOURCE_H
#define TIME_SOURCE_H

#include "binding_macros.h"

#include <functional>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectExecutionContext;

class EffectTimer : public RefCounted {
    GDCLASS(EffectTimer, RefCounted)

public:
    void set_callback(std::function<void()> p_callback);
    virtual void stop() = 0;

protected:
    std::function<void()> callback;

    static void _bind_methods();
};

class TimeSource : public Resource {
    GDCLASS(TimeSource, Resource)

public:
    virtual Ref<EffectTimer> create_timer(const EffectExecutionContext& execution_context, float duration) const = 0;
    virtual Ref<EffectTimer> create_interval(const EffectExecutionContext& execution_context, float duration) const = 0;

protected:
    static void _bind_methods();
};

#endif
