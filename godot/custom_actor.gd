extends GameplayActor

@export var initial_effects: Array[GameplayEffect] = []

func _ready():
	for effect in initial_effects:
		apply_effect_to_self(effect)

# TODO: Override virtual method
func _make_effect_spec():
	return super.make_effect_spec()
