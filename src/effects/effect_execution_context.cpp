#include "effects/effect_application_context.h"
#include "gameplay_actor.h"

void EffectApplicationContext::_bind_methods() {
    BIND_METHOD(EffectApplicationContext, get_spec)
    BIND_METHOD(EffectApplicationContext, get_target_actor)
}

ActorSnapshot EffectApplicationContext::get_target_snapshot() const {
    if (target_snapshot) {
        return *target_snapshot;
    }
    return ActorSnapshot{};
}

void EffectApplicationContext::set_target_snapshot(const ActorSnapshot& p_target_snapshot) {
    target_snapshot = std::make_unique<ActorSnapshot>(p_target_snapshot);
}

GET_SET_PROPERTY_IMPL(EffectApplicationContext, Ref<GameplayEffectSpec>, spec)
GET_SET_OBJECT_PTR_IMPL(EffectApplicationContext, GameplayActor, target_actor)

bool EffectApplicationContext::operator==(const EffectApplicationContext& other) const {
    return spec == other.spec
        && target_actor_id == other.target_actor_id
        && target_snapshot == other.target_snapshot;
}
