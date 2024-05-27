extends Node2D

var test_stat: GameplayStat = preload("res://test_stat.tres")

@export var effects: Array[GameplayEffect] = []
var x: Timer

func _ready():
	for effect in effects:
		%Source.apply_effect_to_target(effect, %Target)
