#include "register_types.h"

#include "gameplay_actor.h"
#include "stats/gameplay_stat.h"
#include "modifiers/modifier_magnitude.h"
#include "modifiers/constant_magnitude.h"
#include "modifiers/stat_modifier.h"
#include "effects/gameplay_effect.h"
#include "effects/gameplay_effect_spec.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void init_gameplay_effects_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_VIRTUAL_CLASS(GameplayActor)
    GDREGISTER_CLASS(GameplayStat)
    GDREGISTER_ABSTRACT_CLASS(ModifierMagnitude)
    GDREGISTER_CLASS(ConstantMagnitude)
    GDREGISTER_CLASS(StatModifier)
    GDREGISTER_CLASS(GameplayEffect)
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
