#include "effects/effect_application_context.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/wrapped.hpp>

#include "effects/time_source.h"

using namespace godot;

void TimeSource::_bind_methods() {
    GDVIRTUAL_BIND(_create_timer, "context", "duration")
    GDVIRTUAL_BIND(_create_interval, "context", "duration")
}

void EffectTimer::_bind_methods() {
    BIND_METHOD(EffectTimer, _on_timeout)
}

Ref<EffectTimer> TimeSource::create_timer(const Ref<EffectApplicationContext>& application_context, const stat_value_t duration) const {
    Object* out_timer;
    if (GDVIRTUAL_CALL(_create_timer, application_context, duration, out_timer)) {
        Ref<EffectTimer> effect_timer;
        effect_timer.instantiate();
        effect_timer->set_timer(out_timer);
        return effect_timer;
    }
    return nullptr;
}

Ref<EffectTimer> TimeSource::create_interval(const Ref<EffectApplicationContext>& application_context, const stat_value_t duration) const {
    Object* out_timer;
    if (GDVIRTUAL_CALL(_create_interval, application_context, duration, out_timer)) {
        Ref<EffectTimer> effect_timer;
        effect_timer.instantiate();
        effect_timer->set_timer(out_timer);
        return effect_timer;
    }
    return nullptr;
}

GDVIRTUAL2RC_IMPL(TimeSource, Object*, _create_timer, Ref<EffectApplicationContext>, stat_value_t)
GDVIRTUAL2RC_IMPL(TimeSource, Object*, _create_interval, Ref<EffectApplicationContext>, stat_value_t)

void EffectTimer::set_callback(const std::function<void()> p_callback) {
    callback = p_callback;
}

EffectTimer::~EffectTimer() {
    stop();
}

Object* EffectTimer::get_timer() const {
    return ObjectDB::get_instance(timer_id);
}

void EffectTimer::set_timer(Object* p_timer) {
    Object* existing_timer = get_timer();
    if (existing_timer == p_timer) return;
    if (existing_timer) {
        existing_timer->disconnect("timeout", callable_mp(this, &EffectTimer::_on_timeout));
    }
    timer_id = p_timer ? p_timer->get_instance_id() : ObjectID();
    if (p_timer) {
        p_timer->connect("timeout", callable_mp(this, &EffectTimer::_on_timeout));
    }
}

void EffectTimer::_on_timeout() {
    if (callback) {
        callback();
    }
}

void EffectTimer::stop() {
    if (Object* current_timer = get_timer()) {
        set_timer(nullptr);
        if (current_timer->has_method("stop")) {
            current_timer->call("stop");
        }
        // TODO: This is weird, do something about it
        if (current_timer->has_method("queue_free")) {
            current_timer->call("queue_free");
        }
    }
}
