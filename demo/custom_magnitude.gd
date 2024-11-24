class_name CustomMagnitude extends ModifierMagnitude

func get_magnitude(context: EffectApplicationContext) -> float:
	var custom_data = context.get_spec().get_context().get_custom_data()
	if custom_data is float:
		return custom_data
	return 0
