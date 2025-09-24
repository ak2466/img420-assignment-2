extends Node

@onready var fading_sprite_node = $FadingSprite

func _ready():
	fading_sprite_node.set_rotation_angle(45)
	fading_sprite_node.start_fade()
