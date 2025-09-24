extends Node

@onready var fading_sprite_node = $FadingSprite
@onready var pop_sprite_node = $PopSprite

func _ready():
	fading_sprite_node.start_animation()
	pop_sprite_node.start_animation()
	
