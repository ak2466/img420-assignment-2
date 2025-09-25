extends Timer

# Get the label node
@onready var timer_label = get_node("/root/Node2D/CanvasLayer/TimeLeft")

# Get the timer node
@onready var timer = get_node("/root/Node2D/Timer")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	timer_label.text = str(timer.time_left)
