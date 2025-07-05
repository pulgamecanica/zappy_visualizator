#include "net/game_connection.h"
#include "net/message_parser.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace zappy;

void GameConnection::_bind_methods() {
  ClassDB::bind_method(D_METHOD("set_port", "port"), &GameConnection::set_port);
  ClassDB::bind_method(D_METHOD("set_host", "host"), &GameConnection::set_host);
  ClassDB::bind_method(D_METHOD("connect_to_server"), &GameConnection::connect_to_server);
  ClassDB::bind_method(D_METHOD("disconnect_from_server"), &GameConnection::disconnect_from_server);
  ClassDB::bind_method(D_METHOD("get_state"), &GameConnection::get_state);
  ClassDB::bind_method(D_METHOD("get_pending_messages"), &GameConnection::get_pending_messages);
  ClassDB::bind_method(D_METHOD("set_world", "p_world"), &GameConnection::set_world);
  
  ADD_SIGNAL(MethodInfo("state_changed"));
  ADD_SIGNAL(MethodInfo("message_received", PropertyInfo(Variant::STRING, "message")));
}

GameConnection::GameConnection()
  : connection_state(DISCONNECTED),
    port(2121),
    host("localhost"),
    stop_thread(false),
    emit_state(false) {
  message_mutex.instantiate();
  read_thread.instantiate();
  client.instantiate();
}

GameConnection::~GameConnection() {
  disconnect_from_server();
}

void GameConnection::connect_to_server() {
  String msg = vformat("Connection attempt on {%s:%d}", host, port);
  UtilityFunctions::print(msg);

  set_state(CONNECTING);
  Error err = client->connect_to_host(host, port);
  if (err != OK) {
    UtilityFunctions::printerr("❌ Failed to connect to host: ", host, ":", port);
    set_state(ERROR);
    return;
  }
  
  stop_thread = false;
  read_thread->start(callable_mp(this, &GameConnection::read_loop));
}

void GameConnection::set_host(const godot::String &p_host) { host = p_host; }

void GameConnection::set_port(int p_port) { port = p_port; }

void GameConnection::set_state(ConnectionState p_state) {
  connection_state = p_state;
  emit_state = true;
}

void GameConnection::emit_state_change() {
  if (emit_state) {
    emit_state = false;
    emit_signal("state_changed");
  }
}

void GameConnection::disconnect_from_server() {
  stop_thread = true;
  if (read_thread.is_valid()) {
    read_thread->wait_to_finish();
    read_thread.unref();
  }

  if (client.is_valid()) {
    client->disconnect_from_host();
  }
  set_state(DISCONNECTED);
}

int GameConnection::get_state() const {
    return static_cast<int>(connection_state);
}

Array GameConnection::get_pending_messages() {
  Array arr;
  message_mutex->lock();
  while (!incoming_messages.empty()) {
    arr.push_back(incoming_messages.front());
    incoming_messages.pop();
  }
  message_mutex->unlock();
  return arr;
}

void GameConnection::_process(double delta) {
  double reconnect_delay = 5.0;

  emit_state_change();

  if (get_state() == DISCONNECTED || get_state() == ERROR) {
      reconnect_delay -= delta;
      if (reconnect_delay <= 0.0) {
        UtilityFunctions::print("Retry connect");

        reconnect_delay = 3.0;
        connect_to_server();
      }
  }

  message_mutex->lock();
  while (!incoming_messages.empty()) {
    String msg = incoming_messages.front();
    incoming_messages.pop();
    message_mutex->unlock();

    zappy::MessageParser::parse_message(msg, world_ref);
    emit_signal("message_received", msg);

    message_mutex->lock();
  }
  message_mutex->unlock();
}

void GameConnection::read_loop() {
  const int poll_interval_ms = 10;
  
  while (!stop_thread) {
    client->poll();

    StreamPeerTCP::Status status = client->get_status();

    if (status != StreamPeerTCP::STATUS_CONNECTED) {
      set_state((status == StreamPeerTCP::STATUS_ERROR) ? ERROR : (status == StreamPeerTCP::STATUS_CONNECTING) ? CONNECTING : DISCONNECTED);  
    } else {
    
      if (get_state() != CONNECTED) {
        set_state(CONNECTED);
      }

      int available = client->get_available_bytes();
      if (available > 0) {
        Array result = client->get_partial_data(available);
        Error err = (Error)(int)result[0];
        PackedByteArray buffer = result[1];

        if (err == OK) {
          String msg = buffer.get_string_from_utf8();

          PackedStringArray lines = msg.split("\n", false);
          for (int i = 0; i < lines.size(); ++i) {
            String line = lines[i].strip_edges();
            if (!line.is_empty()) {
                message_mutex->lock();
                incoming_messages.push(line);
                message_mutex->unlock();
            }
          }
        } else if (err != ERR_UNAVAILABLE) {
          UtilityFunctions::printerr("❌ Error reading from socket: ", err);
        }
      }
    }
    OS::get_singleton()->delay_msec(poll_interval_ms);
  }
}

void GameConnection::set_world(World *p_world) {
    world_ref = p_world;
}