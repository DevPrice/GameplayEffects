#include "effects/gameplay_effect_context.h"
#include "gameplay_actor.h"

#include <godot_cpp/core/class_db.hpp>

void GameplayEffectContext::_bind_methods() {
    BIND_METHOD(GameplayEffectContext, get_source_actor)
    BIND_METHOD(GameplayEffectContext, get_custom_data)
}

std::shared_ptr<ActorSnapshot> GameplayEffectContext::get_source_snapshot() const {
    return source_snapshot;
}

void GameplayEffectContext::set_source_snapshot(const ActorSnapshot& actor_snapshot) {
    source_snapshot = std::make_shared<ActorSnapshot>(actor_snapshot);
}

GET_SET_OBJECT_PTR_IMPL(GameplayEffectContext, GameplayActor, source_actor)
GET_SET_PROPERTY_IMPL(GameplayEffectContext, Variant, custom_data)
