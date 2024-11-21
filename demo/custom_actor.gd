class_name CustomActor extends GameplayActor

static var test_stat: GameplayStat = preload("res://test_stat.tres")
static var max_stat: GameplayStat = preload("res://max_stat.tres")

@export var initial_effects: Array[GameplayEffect] = []

func _ready():
	receiving_effect.connect(
		func (spec: GameplayEffectSpec):
			print("[%s] Receiving effect: '%s'" % [name, spec.get_effect().resource_name])
	)
	received_effect.connect(
		func (spec: GameplayEffectSpec):
			print("[%s] Received effect: '%s'" % [name, spec.get_effect().resource_name])
	)
	stat_changed.connect(
		func (stat: GameplayStat, new_value: float, old_value: float):
			print("[%s] %s: %s -> %s" % [name, stat.resource_name, old_value, new_value])
	)
	tags_changed.connect(
		func (added: Array[String], removed: Array[String]):
			print("[%s]: Added=%s, Removed=%s" % [name, added, removed])
	)
	for effect in initial_effects:
		apply_effect_to_self(effect)

func _get_custom_context_data():
	return 1337.0
