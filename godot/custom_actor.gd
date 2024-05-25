extends GameplayActor

@export var initial_effects: Array[GameplayEffect] = []

func _ready():
	receiving_effect.connect(
		func (spec: GameplayEffectSpec): print("%s receiving effect '%s'..." % [name, spec.effect.resource_name])
	)
	received_effect.connect(
		func (spec: GameplayEffectSpec): print("%s received effect '%s'." % [name, spec.effect.resource_name])
	)
	for effect in initial_effects:
		apply_effect_to_self(effect)

# TODO: Override virtual method
func _make_effect_spec(effect: GameplayEffect):
	return super.make_effect_spec(effect)
