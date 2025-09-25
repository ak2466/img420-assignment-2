extends Area2D

@onready var timer = $"../Timer"
@onready var animation = $FadeAnim

@onready var win_menu = get_node("/root/Node2D/CanvasLayer/WinScreen")

func _on_body_entered(body: Node2D) -> void:
	
	# Disable monitoring to prevent accidental recaptures
	self.set_deferred("monitoring", false)
	
	# Add 3 seconds to timer
	timer.wait_time += 3
	timer.start()
	
	# Trigger animation on item
	animation.start_animation()
	
	# Wait for animation to complete
	await animation.animation_complete
	
	# Free from the queue
	queue_free()
	
	# Stop time scale
	Engine.time_scale = 0
	
	# Show menu
	win_menu.show()
