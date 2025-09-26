extends Area2D

@onready var timer = $"../Timer"
@onready var animation = $FadeAnim




func _on_body_entered(body: Node2D) -> void:
	
	# Disable monitoring to prevent accidental recaptures
	self.set_deferred("monitoring", false)
	
	# Add 3 seconds to timer
	timer.wait_time += 3
	timer.start()
	
	# Trigger animation on item
	animation.start_animation(false, false)
	
	# Wait for animation to complete
	await animation.animation_complete
	
	# Free from the queue
	queue_free()


func _on_player_game_started() -> void:
	
	animation.set_deferred("reverse_animation", true)
	animation.set_deferred("reverse_fade", true)
	
	await get_tree().process_frame
	animation.start_animation(true, true)
	
	await animation.animation_complete
