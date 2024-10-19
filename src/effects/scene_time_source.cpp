#include "gameplay_actor.h"
#include "effects/effect_execution_context.h"
#include "effects/scene_time_source.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

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

Ref<EffectTimer> SceneTimeSource::create_timer(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration) const {
    return _create_timer(execution_context, duration, true);
}

Ref<EffectTimer> SceneTimeSource::create_interval(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration) const {
    return _create_timer(execution_context, duration, false);
}

Ref<EffectTimer> SceneTimeSource::_create_timer(const Ref<EffectExecutionContext>& execution_context, stat_value_t duration, bool one_shot) const {
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

Timer* SceneEffectTimer::get_timer() const {
    return Object::cast_to<Timer>(ObjectDB::get_instance(timer_id));
}

void SceneEffectTimer::set_timer(Timer* p_timer) {
    Timer* existing_timer = get_timer();
    if (existing_timer == p_timer) return;
    if (existing_timer) {
        existing_timer->disconnect("timeout", callable_mp(this, &SceneEffectTimer::_on_timeout));
    }
    timer_id = p_timer ? p_timer->get_instance_id() : ObjectID();
    if (p_timer) {
        p_timer->connect("timeout", callable_mp(this, &SceneEffectTimer::_on_timeout));
    }
}

void SceneEffectTimer::_on_timeout() {
    if (callback) {
        callback();
    }
}

void SceneEffectTimer::stop() {
    Timer* current_timer = get_timer();
    if (current_timer) {
        set_timer(nullptr);
        current_timer->stop();
        current_timer->queue_free();
    }
}
