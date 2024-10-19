#ifndef ACTOR_SNAPSHOT_H
#define ACTOR_SNAPSHOT_H

#include "typedefs.h"
#include "stats/gameplay_stat.h"
#include "modifiers/evaluated_modifier.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <memory>
#include <vector>

struct StatSnapshot {
    stat_value_t base_value = STAT_ZERO;
    stat_value_t current_value = STAT_ZERO;
};

struct ActorSnapshot {
    const HashMap<Ref<GameplayStat>, StatSnapshot> base_value_snapshot;
    const std::vector<std::shared_ptr<EvaluatedModifier>> modifier_snapshot;

    bool operator==(const ActorSnapshot &other) const {
        // TODO: base_value_snapshot
        return modifier_snapshot == other.modifier_snapshot;
    }
};

#endif
