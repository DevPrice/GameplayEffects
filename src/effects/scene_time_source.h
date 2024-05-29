#ifndef SCENE_TIME_SOURCE_H
#define SCENE_TIME_SOURCE_H

#include "binding_macros.h"
#include "effects/time_source.h"

#include <functional>
#include <godot_cpp/classes/timer.hpp>

using namespace godot;

class SceneEffectTimer : public EffectTimer {
    GDCLASS(SceneEffectTimer, EffectTimer)

public:
    ~SceneEffectTimer();
    void set_timer(Timer* p_timer);
    void stop() override;

private:
    Timer* timer;

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

    Ref<EffectTimer> create_timer(const EffectExecutionContext& execution_context, float duration) const override;
    Ref<EffectTimer> create_interval(const EffectExecutionContext& execution_context, float duration) const override;

private:
    Ref<EffectTimer> _create_timer(const EffectExecutionContext& execution_context, float duration, bool one_shot) const;

protected:
    static void _bind_methods();
};

#endif
