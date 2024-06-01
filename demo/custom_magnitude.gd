class_name CustomMagnitude extends CustomMagnitudeCalculation

func _get_magnitude(context: EffectExecutionContext) -> float:
	var custom_data = context.get_spec().get_context().get_custom_data()
	if custom_data is float:
		return custom_data
	return 0
