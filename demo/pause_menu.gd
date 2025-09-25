extends Control

signal pause_requested()

func _on_resume_pressed() -> void:
	pause_requested.emit()

func _on_quit_pressed() -> void:
	get_tree().quit()
