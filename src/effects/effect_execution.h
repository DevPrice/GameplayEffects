#ifndef EFFECT_EXECUTION_H
#define EFFECT_EXECUTION_H

#include "binding_macros.h"

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class EffectExecutionContext;

class EffectExecutionOutput : public RefCounted {
    GDCLASS(EffectExecutionOutput, RefCounted)

protected:
    static void _bind_methods();
};

class EffectExecution : public Resource {
    GDCLASS(EffectExecution, Resource)

public:
    virtual void execute(const EffectExecutionContext& execution_context, Ref<EffectExecutionOutput> output) = 0;

protected:
    static void _bind_methods();
};

#endif
