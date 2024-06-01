class_name CustomMagnitude extends CustomMagnitudeCalculation

func _get_magnitude(context: EffectExecutionContext) -> float:
	return context.get_target_actor().name.length()
