#include "effects/effect_component.h"
#include "effects/effect_execution.h"
#include "effects/effect_lifetime.h"
#include "effects/gameplay_effect.h"
#include "effects/gameplay_effect_context.h"
#include "effects/gameplay_effect_spec.h"
#include "effects/gameplay_requirements.h"
#include "effects/time_source.h"
#include "effects/scene_time_source.h"
#include "modifiers/clamped_magnitude.h"
#include "modifiers/constant_magnitude.h"
#include "modifiers/curve_sample_magnitude.h"
#include "modifiers/modifier_channel.h"
#include "modifiers/modifier_magnitude.h"
#include "modifiers/scaled_magnitude.h"
#include "modifiers/stat_based_magnitude.h"
#include "modifiers/stat_modifier.h"
#include "modifiers/tag_based_magnitude.h"
#include "modifiers/custom_magnitude_calculation.h"
#include "stats/captured_stat.h"
#include "stats/gameplay_stat.h"
#include "stats/stat_component.h"
#include "stats/stat_evaluator.h"
#include "gameplay_actor.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "register_types.h"

using namespace godot;

void init_gameplay_effects_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_VIRTUAL_CLASS(GameplayActor)
    GDREGISTER_CLASS(ActiveEffectHandle)
    GDREGISTER_CLASS(GameplayStat)
    GDREGISTER_ABSTRACT_CLASS(ModifierMagnitude)
    GDREGISTER_CLASS(ConstantMagnitude)
    GDREGISTER_CLASS(ClampedMagnitude)
    GDREGISTER_CLASS(ScaledMagnitude)
    GDREGISTER_CLASS(StatBasedMagnitude)
    GDREGISTER_CLASS(TagBasedMagnitude)
    GDREGISTER_CLASS(CurveSampleMagnitude)
    GDREGISTER_VIRTUAL_CLASS(CustomMagnitudeCalculation)
    GDREGISTER_CLASS(ModifierChannel)
    GDREGISTER_CLASS(StatModifier)
    GDREGISTER_CLASS(CapturedStat)
    GDREGISTER_CLASS(StatEvaluator)
    GDREGISTER_VIRTUAL_CLASS(StatComponent)
    GDREGISTER_ABSTRACT_CLASS(GameplayRequirements)
    GDREGISTER_ABSTRACT_CLASS(EffectTimer)
    GDREGISTER_ABSTRACT_CLASS(TimeSource)
    GDREGISTER_CLASS(SceneEffectTimer)
    GDREGISTER_CLASS(SceneTimeSource)
    GDREGISTER_CLASS(EffectExecutionContext)
    GDREGISTER_CLASS(EffectExecutionOutput)
    GDREGISTER_VIRTUAL_CLASS(EffectExecution)
    GDREGISTER_CLASS(EffectLifetime)
    GDREGISTER_CLASS(GameplayEffect)
    GDREGISTER_CLASS(GameplayEffectContext)
    GDREGISTER_CLASS(GameplayEffectSpec)
}

void uninit_gameplay_effects_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gameplay_effects_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(init_gameplay_effects_module);
    init_obj.register_terminator(uninit_gameplay_effects_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
