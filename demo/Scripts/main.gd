extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var summator = Summator.new();
	summator.add(5)
	summator.add(2)
	print(summator.get_total())

func _on_button_pressed() -> void:
	$TrafficLight.show_next_light()


func _on_traffic_light_light_changed(new_light: int) -> void:
	print(new_light)
