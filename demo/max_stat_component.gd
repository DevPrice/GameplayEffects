class_name MaxStatComponent extends EffectComponent

func _on_base_value_changing(context: EffectExecutionContext, stat: GameplayStat, new_value: float) -> float:
	if stat == CustomActor.test_stat:
		var max_value := context.get_target_actor().get_stat_current_value(CustomActor.max_stat)
		return min(new_value, max_value)
	return new_value

func _on_current_value_changing(context: EffectExecutionContext, stat: GameplayStat, new_value: float) -> float:
	if stat == CustomActor.test_stat:
		var max_value := context.get_target_actor().get_stat_current_value(CustomActor.max_stat)
		return min(new_value, max_value)
	return new_value
