extends Area2D

@onready var timer = $"../Timer"
@onready var animation = $FadeAnim

@onready var win_menu = get_node("/root/Node2D/CanvasLayer/WinScreen")

func _on_body_entered(body: Node2D) -> void:
	
	if body.is_in_group("Player"):
		
		body.set_process_mode(Node.PROCESS_MODE_DISABLED)
	
		# Disable monitoring to prevent accidental recaptures
		self.set_deferred("monitoring", false)
	
		# Trigger animation on item
		animation.start_animation()
	
		# Wait for animation to complete
		await animation.animation_complete
		
		Engine.time_scale = 0
	
		# Free from the queue
		queue_free()
		
		# Show menu
		win_menu.show()
