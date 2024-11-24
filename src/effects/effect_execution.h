#ifndef EFFECT_EXECUTION_H
#define EFFECT_EXECUTION_H

#include "binding_macros.h"
#include "virtual_macros.h"
#include "typedefs.h"
#include "modifiers/evaluated_modifier.h"
#include "modifiers/stat_modifier.h"
#include "stats/stat_evaluator.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <memory>
#include <vector>

using namespace godot;

class EffectApplicationContext;

class EffectExecutionOutput : public RefCounted {
    GDCLASS(EffectExecutionOutput, RefCounted)

public:
    std::vector<std::shared_ptr<EvaluatedModifier>> get_modifiers() const;
    void add_modifier(const Ref<GameplayStat>& stat, StatModifier::Operation operation, stat_value_t magnitude);

private:
    std::vector<std::shared_ptr<EvaluatedModifier>> modifiers;

protected:
    static void _bind_methods();
};

class EffectExecution : public Resource {
    GDCLASS(EffectExecution, Resource)

public:
    virtual void execute(const Ref<EffectApplicationContext>& application_context, const Ref<StatEvaluator>& stat_evaluator, const Ref<EffectExecutionOutput>& output);

protected:
    GDVIRTUAL3_NO_IMPL(_execute, const Ref<EffectApplicationContext>&, const Ref<StatEvaluator>&, const Ref<EffectExecutionOutput>&)

protected:
    static void _bind_methods();
};

#endif
