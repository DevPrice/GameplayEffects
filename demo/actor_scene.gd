extends Node2D

@export var effects: Array[GameplayEffect] = []

func _ready():
	var tags: GameplayTagContainer = %Target.get_loose_tags()
	tags.add_tag("init.tag")
	for effect in effects:
		%Source.apply_effect_to_target(effect, %Target, {"test.tag": 2})
	test_tag("parent.test")
	tags.add_tag("parent.test.child")
	tags.add_tag("parent.test.child.blahblah")
	print("Loose tags: ", tags.to_array())
	print("Granted tags: ", %Target.get_granted_tags())

func test_tag(tag: String, exact: bool = false):
	if exact:
		print("%s: %s" % [tag, %Target.has_tag_exact(tag)])
	else:
		print("%s: %s" % [tag, %Target.has_tag(tag)])
