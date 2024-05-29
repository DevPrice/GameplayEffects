#ifndef ACTOR_SNAPSHOT_H
#define ACTOR_SNAPSHOT_H

#include "stats/gameplay_stat.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <memory>
#include <vector>

class IEvaluatedModifier;

struct StatSnapshot {
    float base_value = 0.f;
    float current_value = 0.f;
};

struct ActorSnapshot {
    const HashMap<Ref<GameplayStat>, StatSnapshot> base_value_snapshot;
    const std::vector<std::shared_ptr<IEvaluatedModifier>> modifier_snapshot;

    bool operator==(const ActorSnapshot &other) const {
        // TODO: base_value_snapshot
        return modifier_snapshot == other.modifier_snapshot;
    }
};

#endif
