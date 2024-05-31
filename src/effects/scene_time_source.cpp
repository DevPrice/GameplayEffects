#include "gameplay_actor.h"
#include "effects/effect_execution_context.h"
#include "effects/scene_time_source.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include "scene_time_source.h"

using namespace godot;

void SceneTimeSource::_bind_methods() {
    BIND_GET_SET(SceneTimeSource, process_always, Variant::BOOL)
    BIND_GET_SET(SceneTimeSource, process_in_physics, Variant::BOOL)
}

void SceneEffectTimer::_bind_methods() {
   BIND_METHOD(SceneEffectTimer, _on_timeout)
}

GET_SET_PROPERTY_IMPL(SceneTimeSource, bool, process_always)
GET_SET_PROPERTY_IMPL(SceneTimeSource, bool, process_in_physics)

Ref<EffectTimer> SceneTimeSource::create_timer(const Ref<EffectExecutionContext>& execution_context, float duration) const {
    return _create_timer(execution_context, duration, true);
}

Ref<EffectTimer> SceneTimeSource::create_interval(const Ref<EffectExecutionContext>& execution_context, float duration) const {
    return _create_timer(execution_context, duration, false);
}

Ref<EffectTimer> SceneTimeSource::_create_timer(const Ref<EffectExecutionContext>& execution_context, float duration, bool one_shot) const {
    Timer* timer = memnew(Timer);
    timer->set_autostart(true);
    timer->set_one_shot(one_shot);
    timer->set_wait_time(duration);
    Ref<SceneEffectTimer> effect_timer = memnew(SceneEffectTimer);
    effect_timer->set_timer(timer);
    if (GameplayActor* target_actor = execution_context.is_valid() ? execution_context->get_target_actor() : nullptr) {
        target_actor->add_child(timer);
    }
    return effect_timer;
}

SceneEffectTimer::~SceneEffectTimer() {
    stop();
}

void SceneEffectTimer::set_timer(Timer* p_timer) {
    if (timer == p_timer) return;
    if (timer) {
        timer->disconnect("timeout", callable_mp(this, &SceneEffectTimer::_on_timeout));
    }
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
        timer = nullptr;
    }
}
