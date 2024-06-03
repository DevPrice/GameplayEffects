#ifndef STAT_COMPONENT_H
#define STAT_COMPONENT_H

#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class GameplayActor;
class GameplayStat;

class StatComponent : public Resource {
    GDCLASS(StatComponent, Resource)

public:
    StatComponent();

    virtual void on_base_value_changing(GameplayActor* actor, const Ref<GameplayStat>& stat, float& ref_new_value);
    virtual void on_base_value_changed(GameplayActor* actor, const Ref<GameplayStat>& stat, float new_value);
    virtual void on_current_value_changing(GameplayActor* actor, const Ref<GameplayStat>& stat, float& ref_new_value);
    virtual void on_current_value_changed(GameplayActor* actor, const Ref<GameplayStat>& stat, float new_value);

    GDVIRTUAL3R_NO_IMPL(float, _on_base_value_changing, GameplayActor*, const Ref<GameplayStat>&, float)
    GDVIRTUAL3_NO_IMPL(_on_base_value_changed, GameplayActor*, const Ref<GameplayStat>&, float)
    GDVIRTUAL3R_NO_IMPL(float, _on_current_value_changing, GameplayActor*, const Ref<GameplayStat>&, float)
    GDVIRTUAL3_NO_IMPL(_on_current_value_changed, GameplayActor*, const Ref<GameplayStat>&, float)

protected:
    static void _bind_methods();
};

#endif
