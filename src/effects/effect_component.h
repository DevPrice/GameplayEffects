#ifndef EFFECT_COMPONENT_H
#define EFFECT_COMPONENT_H

#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectExecutionContext;

class EffectComponent : public Resource {
    GDCLASS(EffectComponent, Resource)

public:
    virtual void on_application(const Ref<EffectExecutionContext>& context);
    virtual void on_removal(const Ref<EffectExecutionContext>& context);

protected:
    GDVIRTUAL1_NO_IMPL(_on_application, const Ref<EffectExecutionContext>&)
    GDVIRTUAL1_NO_IMPL(_on_removal, const Ref<EffectExecutionContext>&)

protected:
    static void _bind_methods();
};

#endif
