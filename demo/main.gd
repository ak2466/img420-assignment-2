extends CharacterBody2D

const SPEED = 300.0
const JUMP_VELOCITY = -500.0

signal game_started

@onready var pause_menu = get_node("/root/Node2D/CanvasLayer/PauseMenu")
@onready var failed_menu = get_node("/root/Node2D/CanvasLayer/FailedMenu")
@onready var timer = get_node("/root/Node2D/Timer")
@onready var start_menu = get_node("/root/Node2D/CanvasLayer/StartMenu")
@onready var win_menu = get_node("/root/Node2D/CanvasLayer/WinScreen")
@onready var extend_time_area = $"../ExtendTimeArea"
@onready var extend_time_sprite = $"../ExtendTimeArea/AnimatedSprite2D"
@onready var extend_time_anim = $"../ExtendTimeArea/FadeAnim"

var paused = false

func _ready():
	
	# Connect the signal to the timeout
	timer.timeout.connect(_on_timer_timeout)
	
	# Set time scale to zero untill start
	Engine.time_scale = 0
	
	# Connect to the restart game signal
	failed_menu.restart_requested.connect(restart_game)
	
	# Connect to the start game signal
	start_menu.start_game.connect(start_game)
	
	# Connect to the start game signal (from won screen)
	win_menu.start_game.connect(restart_game)
	


func _process(_delta: float):
	
	# Check if pause is triggered
	if Input.is_action_just_pressed("pause"):
		
		# Call pause menu
		pauseMenu()
		
	# Get viewport y size
	var y_size = get_viewport_rect().size.y
	
	# Check if player's y position is greater
	if position.y > y_size:
		
		failed_game()
		
		print("Y position exceeded.")
		
func pauseMenu():
	
	# Check if currently paused
	if paused:
		
		# If paused and pause called,
		# Hide pause menu
		pause_menu.hide()
		
		# Resume time progression
		Engine.time_scale = 1
		
	# Otherwise, if pause menu not shown and pause called
	else:
		
		# Show the pause menu
		pause_menu.show()
		
		# Stop the time progressin
		Engine.time_scale = 0
		
	# Flip the time variable
	paused = !paused

func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity += get_gravity() * delta

	# Handle jump.
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction := Input.get_axis("ui_left", "ui_right")
	if direction:
		velocity.x = direction * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)

	move_and_slide()

# Pause signal receiver
func _on_pause_menu_pause_requested() -> void:
	
	# Call pause menu
	pauseMenu()

# Timer signal receiver
func _on_timer_timeout() -> void:
	
	print("Timer out.")
	
	# Call failed game
	failed_game()
	
# Restart signal receiver
func restart_game() -> void:
	
	get_tree().reload_current_scene()
	
	print("Game restarted.")
	
func start_game():
	
	# Reset time scale
	Engine.time_scale = 1
	
	# Emit the game started signal
	emit_signal("game_started")
	
	# Start the timer
	timer.start()
	
	# Hide the start menu
	start_menu.hide()
	
	# Hide the win menu
	win_menu.hide()
	
func failed_game():
	
	print("Failed game")
	
	# Stop the game
	Engine.time_scale = 0
	
	# Show failed menu
	failed_menu.show()


func _on_pause_button_pressed() -> void:
	
	pauseMenu()
	
