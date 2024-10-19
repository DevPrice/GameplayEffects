class_name MaxStatComponent extends EffectComponent

func _on_base_value_changing(context: EffectExecutionContext, _stat: GameplayStat, new_value: float) -> float:
	var max_value := context.get_target_actor().get_stat_current_value(CustomActor.max_stat)
	return min(new_value, max_value)

func _on_current_value_changing(context: EffectExecutionContext, _stat: GameplayStat, new_value: float) -> float:
	var max_value := context.get_target_actor().get_stat_current_value(CustomActor.max_stat)
	return min(new_value, max_value)
