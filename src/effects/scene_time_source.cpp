#include "gameplay_actor.h"
#include "effects/effect_execution_context.h"
#include "effects/scene_time_source.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void SceneTimeSource::_bind_methods() {
   
}

void SceneEffectTimer::_bind_methods() {
   ClassDB::bind_method(D_METHOD("_on_timeout"), &SceneEffectTimer::_on_timeout);
}

Ref<EffectTimer> SceneTimeSource::create_timer(const EffectExecutionContext& execution_context, float duration) const {
    return _create_timer(execution_context, duration, true);
}

Ref<EffectTimer> SceneTimeSource::create_interval(const EffectExecutionContext& execution_context, float duration) const {
    return _create_timer(execution_context, duration, false);
}

Ref<EffectTimer> SceneTimeSource::_create_timer(const EffectExecutionContext& execution_context, float duration, bool one_shot) const {
    Timer* timer = memnew(Timer);
    timer->set_autostart(true);
    timer->set_one_shot(one_shot);
    timer->set_wait_time(duration);
    Ref<SceneEffectTimer> effect_timer = memnew(SceneEffectTimer);
    effect_timer->set_timer(timer);
    execution_context.target_actor->add_child(timer);
    return effect_timer;
}

void SceneEffectTimer::set_timer(Timer* p_timer) {
    timer = p_timer;
    if (timer) {
        timer->connect("timeout", callable_mp(this, &SceneEffectTimer::_on_timeout));
    }
}

void SceneEffectTimer::_on_timeout() {
    if (callback) {
        callback();
    }
}

void SceneEffectTimer::stop() {
    if (timer) {
        callback = nullptr;
        timer->stop();
        timer->queue_free();
    }
}
