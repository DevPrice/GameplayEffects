extends Control

@export var actor: GameplayActor
@export var stat: GameplayStat
@export var max_stat: GameplayStat

@export var title: RichTextLabel
@export var stat_bar: ProgressBar
@export var stat_label: RichTextLabel

@export var tag_list: ItemList

func _ready() -> void:
	if actor:
		if title:
			title.text = actor.name
		if stat_bar and stat and max_stat:
			stat_bar.value = actor.get_stat_current_value(stat)
			stat_bar.max_value = actor.get_stat_current_value(max_stat)
			actor.current_value_changed(stat).connect(
				func (new_value: float, _old_value: float):
					stat_bar.value = new_value
					_update_value_label()
			)
			actor.current_value_changed(max_stat).connect(
				func (new_value: float, _old_value: float):
					stat_bar.max_value = new_value
					_update_value_label()
			)
		actor.tags_changed.connect(
			func (_added_tags: Array[String], _removed_tags: Array[String]):
				_update_tags()
		)
	_update_tags()
	_update_value_label()

func _update_value_label() -> void:
	if stat_label and actor and stat and max_stat:
		stat_label.text = "%s/%s" % [actor.get_stat_current_value(stat), actor.get_stat_current_value(max_stat)]

func _update_tags() -> void:
	if actor and tag_list:
		tag_list.clear()
		var tags := actor.get_granted_tags()
		tags.append_array(actor.get_loose_tags().to_array())
		for tag in tags:
			tag_list.add_item(tag, null, false)
