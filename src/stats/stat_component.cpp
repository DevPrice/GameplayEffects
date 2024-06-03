#include "stats/gameplay_stat.h"
#include "gameplay_actor.h"

#include "stats/stat_component.h"

void StatComponent::_bind_methods() {
    GDVIRTUAL_BIND(_on_base_value_changing, "actor", "stat", "new_value")
    GDVIRTUAL_BIND(_on_base_value_changed, "actor", "stat", "new_value")
    GDVIRTUAL_BIND(_on_current_value_changing, "actor", "stat", "new_value")
    GDVIRTUAL_BIND(_on_current_value_changed, "actor", "stat", "new_value")
}

StatComponent::StatComponent() { }

void StatComponent::on_base_value_changing(GameplayActor* actor, const Ref<GameplayStat>& stat, float& ref_new_value) {
    GDVIRTUAL_CALL(_on_base_value_changing, actor, stat, ref_new_value, ref_new_value);
}

void StatComponent::on_base_value_changed(GameplayActor* actor, const Ref<GameplayStat>& stat, float new_value) {
    GDVIRTUAL_CALL(_on_base_value_changed, actor, stat, new_value);
}

void StatComponent::on_current_value_changing(GameplayActor* actor, const Ref<GameplayStat>& stat, float& ref_new_value) {
    GDVIRTUAL_CALL(_on_current_value_changing, actor, stat, ref_new_value, ref_new_value);
}

void StatComponent::on_current_value_changed(GameplayActor* actor, const Ref<GameplayStat>& stat, float new_value) {
    GDVIRTUAL_CALL(_on_current_value_changed, actor, stat, new_value);
}

GDVIRTUAL3R_IMPL(StatComponent, float, _on_base_value_changing, GameplayActor*, Ref<GameplayStat>, float)
GDVIRTUAL3_IMPL(StatComponent, _on_base_value_changed, GameplayActor*, Ref<GameplayStat>, float)
GDVIRTUAL3R_IMPL(StatComponent, float, _on_current_value_changing, GameplayActor*, Ref<GameplayStat>, float)
GDVIRTUAL3_IMPL(StatComponent, _on_current_value_changed, GameplayActor*, Ref<GameplayStat>, float)
