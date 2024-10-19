#ifndef EFFECT_COMPONENT_H
#define EFFECT_COMPONENT_H

#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectExecutionContext;
class GameplayStat;

class EffectComponent : public Resource {
    GDCLASS(EffectComponent, Resource)

public:
    virtual void on_application(const Ref<EffectExecutionContext>& context);
    virtual void on_removal(const Ref<EffectExecutionContext>& context);

    virtual void on_base_value_changing(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, float& ref_new_value);
    virtual void on_base_value_changed(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, float new_value);
    virtual void on_current_value_changing(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, float& ref_new_value);
    virtual void on_current_value_changed(const Ref<EffectExecutionContext>& context, const Ref<GameplayStat>& stat, float new_value);

protected:
    GDVIRTUAL1_NO_IMPL(_on_application, const Ref<EffectExecutionContext>&)
    GDVIRTUAL1_NO_IMPL(_on_removal, const Ref<EffectExecutionContext>&)

    GDVIRTUAL3R_NO_IMPL(float, _on_base_value_changing, const Ref<EffectExecutionContext>&, const Ref<GameplayStat>&, float)
    GDVIRTUAL3_NO_IMPL(_on_base_value_changed, const Ref<EffectExecutionContext>&, const Ref<GameplayStat>&, float)
    GDVIRTUAL3R_NO_IMPL(float, _on_current_value_changing, const Ref<EffectExecutionContext>&, const Ref<GameplayStat>&, float)
    GDVIRTUAL3_NO_IMPL(_on_current_value_changed, const Ref<EffectExecutionContext>&, const Ref<GameplayStat>&, float)

protected:
    static void _bind_methods();
};

#endif
