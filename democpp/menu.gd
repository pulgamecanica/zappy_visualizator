extends Node

const STATE_DISCONNECTED := 0
const STATE_CONNECTING := 1
const STATE_CONNECTED := 2
const STATE_ERROR := 3

@onready var start_button = $CenterContainer/VBoxContainer/StartButton
@onready var status_light = $StatusLight

func _ready():
	WorldManager.connection.connect("state_changed", _on_conn_state)
	_update_ui_state()
	start_button.pressed.connect(_on_start_pressed)

func _on_start_pressed():
	get_tree().change_scene_to_file("res://game_visualization.tscn")

func _on_conn_state():
	_update_ui_state()

func _update_ui_state():
	var state = WorldManager.connection.get_state()
	start_button.disabled = true

	match state:
		STATE_DISCONNECTED:
			status_light.modulate = Color.RED
			status_light.tooltip_text = "Disconnected"
		STATE_CONNECTING:
			status_light.modulate = Color.YELLOW
			status_light.tooltip_text = "Connecting..."
		STATE_CONNECTED:
			status_light.modulate = Color.GREEN
			status_light.tooltip_text = "Connected"
			start_button.disabled = false
		STATE_ERROR:
			status_light.modulate = Color.DARK_RED
			status_light.tooltip_text = "Error"
