#include "effects/effect_execution_context.h"

#include "effects/effect_component.h"

using namespace godot;

void EffectComponent::_bind_methods() {
    GDVIRTUAL_BIND(_on_application, "context")
    GDVIRTUAL_BIND(_on_removal, "context")
}

void EffectComponent::on_application(const Ref<EffectExecutionContext>& context) {
    GDVIRTUAL_CALL(_on_application, context);
}

void EffectComponent::on_removal(const Ref<EffectExecutionContext>& context) {
    GDVIRTUAL_CALL(_on_removal, context);
}

GDVIRTUAL1_IMPL(EffectComponent, _on_application, Ref<EffectExecutionContext>)
GDVIRTUAL1_IMPL(EffectComponent, _on_removal, Ref<EffectExecutionContext>)
