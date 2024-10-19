#include "effects/effect_execution_context.h"
#include "stats/gameplay_stat.h"

#include "effects/effect_component.h"

using namespace godot;

void EffectComponent::_bind_methods() {
    GDVIRTUAL_BIND(_on_application, "context")
    GDVIRTUAL_BIND(_on_removal, "context")

    GDVIRTUAL_BIND(_on_base_value_changing, "context", "stat", "new_value")
    GDVIRTUAL_BIND(_on_base_value_changed, "context", "stat", "new_value")
    GDVIRTUAL_BIND(_on_current_value_changing, "context", "stat", "new_value")
    GDVIRTUAL_BIND(_on_current_value_changed, "context", "stat", "new_value")
}

void EffectComponent::on_application(const Ref<EffectExecutionContext>& context) {
    GDVIRTUAL_CALL(_on_application, context);
}

void EffectComponent::on_removal(const Ref<EffectExecutionContext>& context) {
    GDVIRTUAL_CALL(_on_removal, context);
}

void EffectComponent::on_base_value_changing(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, stat_value_t& ref_new_value) {
    GDVIRTUAL_CALL(_on_base_value_changing, context, stat, ref_new_value, ref_new_value);
}

void EffectComponent::on_base_value_changed(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, stat_value_t new_value) {
    GDVIRTUAL_CALL(_on_base_value_changed, context, stat, new_value);
}

void EffectComponent::on_current_value_changing(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, stat_value_t& ref_new_value) {
    GDVIRTUAL_CALL(_on_current_value_changing, context, stat, ref_new_value, ref_new_value);
}

void EffectComponent::on_current_value_changed(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, stat_value_t new_value) {
    GDVIRTUAL_CALL(_on_current_value_changed, context, stat, new_value);
}

GDVIRTUAL1_IMPL(EffectComponent, _on_application, Ref<EffectExecutionContext>)
GDVIRTUAL1_IMPL(EffectComponent, _on_removal, Ref<EffectExecutionContext>)

GDVIRTUAL3R_IMPL(EffectComponent, stat_value_t, _on_base_value_changing, Ref<EffectExecutionContext>, Ref<GameplayStat>, stat_value_t)
GDVIRTUAL3_IMPL(EffectComponent, _on_base_value_changed, Ref<EffectExecutionContext>, Ref<GameplayStat>, stat_value_t)
GDVIRTUAL3R_IMPL(EffectComponent, stat_value_t, _on_current_value_changing, Ref<EffectExecutionContext>, Ref<GameplayStat>, stat_value_t)
GDVIRTUAL3_IMPL(EffectComponent, _on_current_value_changed, Ref<EffectExecutionContext>, Ref<GameplayStat>, stat_value_t)
