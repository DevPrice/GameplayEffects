#include "effects/effect_execution_context.h"
#include "gameplay_actor.h"

void EffectExecutionContext::_bind_methods() {
    BIND_METHOD(EffectExecutionContext, get_spec)
    BIND_METHOD(EffectExecutionContext, get_target_actor)
}

ActorSnapshot EffectExecutionContext::get_target_snapshot() const {
    return ActorSnapshot();
}

void EffectExecutionContext::set_target_snapshot(const ActorSnapshot& p_target_snapshot) {
    target_snapshot = std::make_unique<ActorSnapshot>(p_target_snapshot);
}

GET_SET_PROPERTY_IMPL(EffectExecutionContext, Ref<GameplayEffectSpec>, spec)
GET_SET_OBJECT_PTR_IMPL(EffectExecutionContext, GameplayActor, target_actor)

bool EffectExecutionContext::operator==(const EffectExecutionContext& other) const {
    return spec == other.spec
        && target_actor_id == other.target_actor_id
        && target_snapshot == other.target_snapshot;
}
