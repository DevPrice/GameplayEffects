#ifndef GAMEPLAY_REQUIREMENTS_H
#define GAMEPLAY_REQUIREMENTS_H

#include "binding_macros.h"
#include "virtual_macros.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectApplicationContext;

class GameplayRequirements : public Resource {
    GDCLASS(GameplayRequirements, Resource)

public:
    virtual bool requirements_met(const Ref<EffectApplicationContext>& application_context);

protected:
    GDVIRTUAL1R_NO_IMPL(bool, _requirements_met, const Ref<EffectApplicationContext>&)

protected:
    static void _bind_methods();
};

#endif
