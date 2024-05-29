#ifndef EFFECT_EXECUTION_H
#define EFFECT_EXECUTION_H

#include "binding_macros.h"
#include "modifiers/stat_modifier.h"
#include "stats/stat_evaluator.h"

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <memory>
#include <vector>

using namespace godot;

class EffectExecutionContext;
class GameplayStat;
class IEvaluatedModifier;

class EffectExecutionOutput : public RefCounted {
    GDCLASS(EffectExecutionOutput, RefCounted)

public:
    std::vector<std::shared_ptr<IEvaluatedModifier>> get_modifiers() const;
    void add_modifier(Ref<GameplayStat> stat, StatModifier::Operation operation, float magnitude);

private:
    std::vector<std::shared_ptr<IEvaluatedModifier>> modifiers;

protected:
    static void _bind_methods();
};

class EffectExecution : public Resource {
    GDCLASS(EffectExecution, Resource)

public:
    virtual void execute(const EffectExecutionContext& execution_context, Ref<StatEvaluator> stat_evaluator, Ref<EffectExecutionOutput> output) = 0;

protected:
    static void _bind_methods();
};

#endif
