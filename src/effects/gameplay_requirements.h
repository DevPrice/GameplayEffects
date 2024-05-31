#ifndef GAMEPLAY_REQUIREMENTS_H
#define GAMEPLAY_REQUIREMENTS_H

#include "binding_macros.h"

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectExecutionContext;

class GameplayRequirements : public Resource {
    GDCLASS(GameplayRequirements, Resource)

public:
    virtual bool requirements_met(const Ref<EffectExecutionContext>& execution_context) const = 0;

protected:
    static void _bind_methods();
};

#endif
