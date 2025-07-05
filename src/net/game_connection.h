#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/stream_peer_tcp.hpp>
#include <queue>
#include "core/world.h"

namespace zappy {

class GameConnection : public godot::Node {
    GDCLASS(GameConnection, godot::Node)

public:
    enum ConnectionState {
        DISCONNECTED,
        CONNECTING,
        CONNECTED,
        ERROR
    };

private:
    godot::Ref<godot::StreamPeerTCP> client;
    ConnectionState connection_state;

    godot::String host;
    int port;

    godot::Ref<godot::Thread> read_thread;

    godot::Ref<godot::Mutex> message_mutex;
    std::queue<godot::String> incoming_messages;

    bool stop_thread;
    bool emit_state;


    World *world_ref = nullptr;
    // Here you can link to your World/Map/Players
    // godot::Ref<World> world;

protected:
    static void _bind_methods();
    void read_loop();

public:
    GameConnection();
    ~GameConnection();

    void connect_to_server();
    void disconnect_from_server();
    void set_host(const godot::String &p_host);
    void set_port(int p_port);
    int get_state() const;
    void set_state(ConnectionState p_state);
    void set_world(World *world);

    void _process(double delta);

    godot::Array get_pending_messages();

    // Signals
    void emit_state_change();
    void emit_message_received(const godot::String& msg);
};

}
