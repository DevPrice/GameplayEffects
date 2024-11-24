#ifndef EFFECT_COMPONENT_H
#define EFFECT_COMPONENT_H

#include "typedefs.h"
#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectApplicationContext;
class GameplayStat;

class EffectComponent : public Resource {
    GDCLASS(EffectComponent, Resource)

public:
    virtual void on_application(const Ref<EffectApplicationContext>& context);
    virtual void on_removal(const Ref<EffectApplicationContext>& context);

    virtual void on_base_value_changing(const Ref<EffectApplicationContext>& context, const Ref<GameplayStat>& stat, stat_value_t& ref_new_value);
    virtual void on_base_value_changed(const Ref<EffectApplicationContext>& context, const Ref<GameplayStat>& stat, stat_value_t new_value);
    virtual void on_current_value_changing(const Ref<EffectApplicationContext>& context, const Ref<GameplayStat>& stat, stat_value_t& ref_new_value);
    virtual void on_current_value_changed(const Ref<EffectApplicationContext>& context, const Ref<GameplayStat>& stat, stat_value_t new_value);

protected:
    GDVIRTUAL1_NO_IMPL(_on_application, const Ref<EffectApplicationContext>&)
    GDVIRTUAL1_NO_IMPL(_on_removal, const Ref<EffectApplicationContext>&)

    GDVIRTUAL3R_NO_IMPL(stat_value_t, _on_base_value_changing, const Ref<EffectApplicationContext>&, const Ref<GameplayStat>&, stat_value_t)
    GDVIRTUAL3_NO_IMPL(_on_base_value_changed, const Ref<EffectApplicationContext>&, const Ref<GameplayStat>&, stat_value_t)
    GDVIRTUAL3R_NO_IMPL(stat_value_t, _on_current_value_changing, const Ref<EffectApplicationContext>&, const Ref<GameplayStat>&, stat_value_t)
    GDVIRTUAL3_NO_IMPL(_on_current_value_changed, const Ref<EffectApplicationContext>&, const Ref<GameplayStat>&, stat_value_t)

protected:
    static void _bind_methods();
};

#endif
