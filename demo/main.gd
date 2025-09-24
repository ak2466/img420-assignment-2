extends Node

@onready var fading_sprite_node = $FadingSprite

func _ready():
	fading_sprite_node.start_animation()
