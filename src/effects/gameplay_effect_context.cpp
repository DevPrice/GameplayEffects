#include "gameplay_effect_context.h"

#include <godot_cpp/core/class_db.hpp>

void GameplayEffectContext::_bind_methods() {
    // TODO: Expose properties
}

std::unique_ptr<ActorSnapshot> GameplayEffectContext::get_source_snapshot() const {
    if (source_snapshot) {
        return std::make_unique<ActorSnapshot>(*source_snapshot);
    }
    return nullptr;
}

void GameplayEffectContext::set_source_snapshot(const ActorSnapshot& actor_snapshot) {
    source_snapshot = std::make_unique<ActorSnapshot>(actor_snapshot);
}

GET_SET_PROPERTY_IMPL(GameplayEffectContext, GameplayActor*, source_actor)
