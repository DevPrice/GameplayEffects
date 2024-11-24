#include "gameplay_actor.h"
#include "effects/effect_application_context.h"
#include "effects/scene_time_source.h"
#include "binding_macros.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

using namespace godot;

void SceneTimeSource::_bind_methods() {
    BIND_GET_SET(SceneTimeSource, process_always, Variant::BOOL)
    BIND_GET_SET(SceneTimeSource, process_in_physics, Variant::BOOL)
}

GET_SET_PROPERTY_IMPL(SceneTimeSource, bool, process_always)
GET_SET_PROPERTY_IMPL(SceneTimeSource, bool, process_in_physics)

Ref<EffectTimer> SceneTimeSource::create_timer(const Ref<EffectApplicationContext>& application_context, stat_value_t duration) const {
    Object* out_timer;
    if (GDVIRTUAL_CALL(_create_timer, application_context, duration, out_timer)) {
        Ref<EffectTimer> effect_timer = memnew(EffectTimer);
        effect_timer->set_timer(out_timer);
        return effect_timer;
    }
    return _create_timer(application_context, duration, true);
}

Ref<EffectTimer> SceneTimeSource::create_interval(const Ref<EffectApplicationContext>& application_context, stat_value_t duration) const {
    Object* out_timer;
    if (GDVIRTUAL_CALL(_create_interval, application_context, duration, out_timer)) {
        Ref<EffectTimer> effect_timer = memnew(EffectTimer);
        effect_timer->set_timer(out_timer);
        return effect_timer;
    }
    return _create_timer(application_context, duration, false);
}

Ref<EffectTimer> SceneTimeSource::_create_timer(const Ref<EffectApplicationContext>& application_context, stat_value_t duration, bool one_shot) const {
    Timer* timer = memnew(Timer);
    timer->set_autostart(true);
    timer->set_one_shot(one_shot);
    timer->set_wait_time(duration);
    timer->set_process_mode(process_always ? Node::PROCESS_MODE_ALWAYS : Node::PROCESS_MODE_INHERIT);
    timer->set_physics_process(process_in_physics);
    Ref<EffectTimer> effect_timer = memnew(EffectTimer);
    effect_timer->set_timer(timer);
    if (GameplayActor* target_actor = application_context.is_valid() ? application_context->get_target_actor() : nullptr) {
        target_actor->add_child(timer);
    }
    return effect_timer;
}
