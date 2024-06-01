#ifndef EFFECT_EXECUTION_H
#define EFFECT_EXECUTION_H

#include "binding_macros.h"
#include "modifiers/evaluated_modifier.h"
#include "modifiers/stat_modifier.h"
#include "stats/stat_evaluator.h"

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <memory>
#include <vector>

using namespace godot;

class EffectExecutionContext;

class EffectExecutionOutput : public RefCounted {
    GDCLASS(EffectExecutionOutput, RefCounted)

public:
    std::vector<std::shared_ptr<EvaluatedModifier>> get_modifiers() const;
    void add_modifier(const Ref<GameplayStat>& stat, StatModifier::Operation operation, float magnitude);

private:
    std::vector<std::shared_ptr<EvaluatedModifier>> modifiers;

protected:
    static void _bind_methods();
};

class EffectExecution : public Resource {
    GDCLASS(EffectExecution, Resource)

public:
    virtual void execute(const Ref<EffectExecutionContext>& execution_context, const Ref<StatEvaluator>& stat_evaluator, const Ref<EffectExecutionOutput>& output);

protected:
    // inlined GDVIRTUAL3 macro to avoid including effect_execution_context.h
    StringName _gdvirtual__execute_sn = "_execute";
    template <bool required>
    _FORCE_INLINE_ bool _gdvirtual__execute_call(const Ref<EffectExecutionContext>& arg1, const Ref<StatEvaluator>& arg2, const Ref<EffectExecutionOutput>& arg3) {
        if (internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual__execute_sn)) {
            GDExtensionCallError ce;
            Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };
            const Variant* vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };
            Variant ret;
            internal::gdextension_interface_object_call_script_method(_owner, &_gdvirtual__execute_sn, (const GDExtensionConstVariantPtr*)vargptrs, 3, &ret, &ce);
            if (ce.error == GDEXTENSION_CALL_OK) {
                return true;
            }
        }
        if (required) {
            ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" "_execute" " must be overridden before calling.");
        }
        return false;
    }
    _FORCE_INLINE_ bool _gdvirtual__execute_overridden() const {
        return internal::gdextension_interface_object_has_script_method(_owner, &_gdvirtual__execute_sn);
    }
    static MethodInfo _gdvirtual__execute_get_method_info();
    // end of inlined macro

protected:
    static void _bind_methods();
};

#endif
