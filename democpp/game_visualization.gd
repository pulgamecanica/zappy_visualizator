extends Node2D

@onready var world_info_panel = $WorldInfoPanel

func _ready():
	world_info_panel.update_info(WorldManager.world)
