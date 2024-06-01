class_name TestExecution extends EffectExecution

@export var operation: StatModifier.Operation = StatModifier.Operation.Offset
@export var magnitude: float = 0

func _execute(_context: EffectExecutionContext, _stat_evaluator: StatEvaluator, output: EffectExecutionOutput) -> void:
	output.add_modifier(CustomActor.test_stat, operation, magnitude)
