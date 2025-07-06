extends Control

const TILE_SIZE = Vector2i(64, 64)
var tile_cache = {}  # Cache of tile data
var resource_textures = {}
var player_textures = {}

func _ready():
	_load_textures()
	_update_tiles()
	_draw()

func _draw():
	for pos in tile_cache.keys():
		print("here pos, ", pos)
		var tile = tile_cache[pos]
		var screen_pos = pos * TILE_SIZE
		draw_rect(Rect2(screen_pos, TILE_SIZE - Vector2i(-5, -5)), Color.PINK)

		# draw resources
		#for rtype in tile.resources:
			#var texture = resource_textures.get(rtype)
			#if texture:
				#draw_texture(texture, screen_pos)
#
		## draw players
		#for player in tile.players:
			#var ptex = player_textures.get(player.orientation)
			#if ptex:
				#draw_texture(ptex, screen_pos + Vector2(8, 8))  # offset for visual

func _update_tiles():
	var tile_data_array = WorldManager.world.get_all_tiles()
	for tile_data in tile_data_array:
		var pos = tile_data["position"]
		var resources = tile_data["resources"]
		var players = tile_data["players"]
		
		tile_cache[pos] = {
			"resources": resources,
			"players": players
		}
		 #draw or update tile based on this info

func _load_textures():
	resource_textures["Copper"] = load("res://assets/resources/Copper.png")
	resource_textures["Diamond"] = load("res://assets/resources/Diamond.png")
	resource_textures["Emerald"] = load("res://assets/resources/Emerald.png")
	resource_textures["Iron"] = load("res://assets/resources/Iron.png")
	resource_textures["Gold"] = load("res://assets/resources/Gold.png")
	resource_textures["Purple"] = load("res://assets/resources/Purple.png")
	player_textures["N"] = load("res://assets/players/marvin_n.png")
	player_textures["S"] = load("res://assets/players/marvin_s.png")
	player_textures["W"] = load("res://assets/players/marvin_l.png")
	player_textures["E"] = load("res://assets/players/marvin_r.png")
