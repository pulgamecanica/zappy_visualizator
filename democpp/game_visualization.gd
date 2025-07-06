extends Control

@onready var world_info_panel = $WorldInfoPanel
@onready var teams_panel = $TeamsPanel
@onready var projection_container = $ProjectionContainer
@onready var selector = $ProjectionSelector

func _ready():
	_load_projection_selector()
	_load_projection(0)
	_update_teams()
	world_info_panel.update_info(WorldManager.world)

func _update_teams():
	var teams = WorldManager.world.get_team_names()
	for team in teams:
		teams_panel.add_item(team)
	var item_height = 32
	var total_height = item_height * teams_panel.item_count
	teams_panel.custom_minimum_size = Vector2(200, total_height)

func _load_projection_selector():
	selector.add_item("Top Down", 0)
	selector.add_item("Isometric", 1)
	selector.add_item("Torus", 2)

func _on_projection_selected(index):
	_load_projection(index)

func _load_projection(index):
	for child in projection_container.get_children():
		child.queue_free()

	var scene_path := ""
	
	match index:
		0:
			scene_path = "res://top_down_map.tscn"
		1:
			scene_path = "res://isometric_map.tscn"
		#2:
			#scene_path = "res://scenes/TorusMap.tscn"
		_:
			return  # or optionally log an error

	var map_scene = load(scene_path).instantiate()
	projection_container.add_child(map_scene)
	#map_scene.render_map(WorldManager.world)
	map_scene._update_tiles()
