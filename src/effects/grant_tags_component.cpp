#include "gameplay_actor.h"
#include "effects/effect_application_context.h"
#include "grant_tags_component.h"

void GrantTagsComponent::_bind_methods() {
    BIND_GET_SET_STRING_ARRAY(GrantTagsComponent, granted_tags)
}

void GrantTagsComponent::on_application(const Ref<EffectApplicationContext>& context) {
    EffectComponent::on_application(context);
    if (context.is_valid()) {
        Ref<GameplayEffectSpec> spec = context->get_spec();
        if (spec.is_valid()) {
            Ref<GameplayEffect> effect = spec->get_effect();
            if (effect.is_valid() && effect->is_instant()) {
                if (GameplayActor* actor = context->get_target_actor()) {
                    Ref<GameplayTagContainer> loose_tags = actor->get_loose_tags();
                    if (loose_tags.is_valid()) {
                        loose_tags->add_tags(granted_tags);
                    }
                }
            }
        }
    }
}

GET_SET_PROPERTY_IMPL(GrantTagsComponent, PackedStringArray, granted_tags)
