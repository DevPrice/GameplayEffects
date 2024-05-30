#include "effects/effect_execution_context.h"
#include "gameplay_actor.h"

GameplayActor* EffectExecutionContext::get_target_actor() const {
    return Object::cast_to<GameplayActor>(ObjectDB::get_instance(target_actor_id));
}
