#ifndef TIME_SOURCE_H
#define TIME_SOURCE_H

#include "binding_macros.h"
#include "virtual_macros.h"
#include "typedefs.h"

#include <functional>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectApplicationContext;

class EffectTimer : public RefCounted {
    GDCLASS(EffectTimer, RefCounted)

    GET_SET_OBJECT_PTR(Object, timer)

public:
    ~EffectTimer() override;
    void set_callback(std::function<void()> p_callback);
    void stop();

private:
    std::function<void()> callback;
    void _on_timeout();

protected:
    static void _bind_methods();
};

class TimeSource : public Resource {
    GDCLASS(TimeSource, Resource)

public:
    virtual Ref<EffectTimer> create_timer(const Ref<EffectApplicationContext>& application_context, stat_value_t duration) const;
    virtual Ref<EffectTimer> create_interval(const Ref<EffectApplicationContext>& application_context, stat_value_t duration) const;

    GDVIRTUAL2RC_REQUIRED_NO_IMPL(Object*, _create_timer, const Ref<EffectApplicationContext>&, stat_value_t)
    GDVIRTUAL2RC_REQUIRED_NO_IMPL(Object*, _create_interval, const Ref<EffectApplicationContext>&, stat_value_t)

protected:
    static void _bind_methods();
};

#endif
