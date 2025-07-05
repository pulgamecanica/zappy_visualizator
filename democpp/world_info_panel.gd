extends Panel

@onready var map_size_label = $VBoxContainer/MapSizeLabel
@onready var player_count_label = $VBoxContainer/PlayerCountLabel
@onready var tick_rate_label = $VBoxContainer/TickRateLabel

func update_info(world):
	var size = world.get_map_dimensions()
	map_size_label.text = "Map Size: %dx%d" % [size.x, size.y]
	player_count_label.text = "Players: %d" % world.get_player_count()
	#tick_rate_label.text = "Tick Rate: %d" % world.get_tick_rate()
