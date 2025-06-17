extends Node

@export var effects: Array[GameplayEffect] = []

func _ready():
	if is_multiplayer_authority():
		%Target.get_loose_tags().add_tag("loose.tag")
		for effect in effects:
			%Source.apply_effect_to_target(effect, %Target, {"test.tag": 2})
