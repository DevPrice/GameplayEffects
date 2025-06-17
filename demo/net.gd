extends Node

@export var port: int = 13337

func _ready() -> void:
	var args := get_cmd_args()
	var arg_connect = args.get("connect")
	if arg_connect is String:
		join_server(arg_connect)
	elif args.get("server"):
		host_server()
	else:
		multiplayer.multiplayer_peer = OfflineMultiplayerPeer.new()
	if multiplayer.is_server() and OS.has_feature("debug"):
		get_window().title = "%s (%s)" % [get_window().title, multiplayer.get_unique_id()]

func _enter_tree() -> void:
	multiplayer.peer_connected.connect(_on_peer_connected, ConnectFlags.CONNECT_DEFERRED)
	multiplayer.peer_disconnected.connect(_on_peer_disconnected, ConnectFlags.CONNECT_DEFERRED)

func _exit_tree() -> void:
	multiplayer.peer_connected.disconnect(_on_peer_connected)
	multiplayer.peer_disconnected.disconnect(_on_peer_disconnected)

func host_server() -> void:
	var peer := ENetMultiplayerPeer.new()
	print("Hosting on port %s..." % port)
	var error := peer.create_server(port)
	if error:
		printerr("[%s] Failed to create server!" % [error])
		return
	multiplayer.multiplayer_peer = peer

func join_server(address: String) -> void:
	var peer := ENetMultiplayerPeer.new()
	print("Connecting to '%s'..." % address)
	var error := peer.create_client(address, port)
	if error:
		printerr("[%s] Failed to create server!" % [error])
		get_tree().quit.call_deferred(error)
	multiplayer.connected_to_server.connect(_connected_to_server)
	multiplayer.connection_failed.connect(_connection_failed)
	multiplayer.multiplayer_peer = peer

func _connected_to_server() -> void:
	print("[%s] Connected to server!" % [multiplayer.get_unique_id()])
	if OS.has_feature("debug"): get_window().title = "%s (%s)" % [get_window().title, multiplayer.get_unique_id()]
	multiplayer.get_peers()

func _connection_failed() -> void:
	get_tree().quit.call_deferred(ERR_CANT_CONNECT)

func _on_peer_connected(id: int):
	print("[%s] %s connected!" % [multiplayer.get_unique_id(), id])

func _on_peer_disconnected(id: int):
	print("[%s] %s disconnected!" % [multiplayer.get_unique_id(), id])
	if not is_multiplayer_authority() and id == get_multiplayer_authority():
		_connection_failed()

static func get_cmd_args() -> Dictionary[String, Variant]:
	var args: Dictionary[String, Variant] = {}
	var args_array := OS.get_cmdline_user_args()
	for arg in args_array:
		var kv := arg.trim_prefix("--").split("=")
		if kv.size() == 2:
			var key := kv[0]
			args[key] = kv[1]
		elif not kv.is_empty():
			args[kv[0]] = true
	if OS.has_feature("web"):
		var url_search: String = JavaScriptBridge.eval("window.location.search")
		var query_param_array := url_search.trim_prefix("?").split("&")
		for arg in query_param_array:
			var kv := arg.trim_prefix("--").split("=")
			if kv.size() == 2:
				var key := kv[0]
				args[key] = kv[1]
			elif not kv.is_empty():
				args[kv[0]] = true
	return args
