#ifndef SCENE_TIME_SOURCE_H
#define SCENE_TIME_SOURCE_H

#include "binding_macros.h"
#include "typedefs.h"
#include "effects/time_source.h"

#include <functional>
#include <godot_cpp/classes/timer.hpp>

using namespace godot;

class SceneEffectTimer : public EffectTimer {
    GDCLASS(SceneEffectTimer, EffectTimer)

    GET_SET_OBJECT_PTR(Timer, timer)

public:
    virtual ~SceneEffectTimer();
    void stop() override;

private:
    void _on_timeout();

protected:
    static void _bind_methods();
};

class SceneTimeSource : public TimeSource {
    GDCLASS(SceneTimeSource, TimeSource)

    GET_SET_PROPERTY(bool, process_always)
    GET_SET_PROPERTY(bool, process_in_physics)

public:
    SceneTimeSource() : process_always(false), process_in_physics(false) { }

    Ref<EffectTimer> create_timer(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration) const override;
    Ref<EffectTimer> create_interval(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration) const override;

private:
    Ref<EffectTimer> _create_timer(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration, bool one_shot) const;

protected:
    static void _bind_methods();
};

#endif
