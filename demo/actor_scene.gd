extends Node2D

@export var effects: Array[GameplayEffect] = []

func _ready():
	for effect in effects:
		%Source.apply_effect_to_target(effect, %Target, {"test.tag": 2})
