extends Control

# Declare signal
signal restart_requested


func _on_restart_pressed() -> void:
	# Emit restart signal
	emit_signal("restart_requested")

func _on_quit_pressed() -> void:
	get_tree().quit()
