extends Node

var world: World
var connection: GameConnection

func _ready():
	world = World.new()
	connection = GameConnection.new()
	connection.set_world(world)
	#connection.connect("message_received", _on_message)
	add_child(connection)
	connection.connect_to_server()

#func _on_message(msg):
	#print("The message is", msg)
