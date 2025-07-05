#pragma once

#include <godot_cpp/classes/node.hpp>
#include <unordered_map>
#include <memory>
#include "tile.h"
#include "player.h"

namespace zappy {

struct Vector2iHash {
    std::size_t operator()(const godot::Vector2i& v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

class World: public godot::Node {
    GDCLASS(World, godot::Node)

protected:
    static void _bind_methods();

public:
    Tile* get_tile(const godot::Vector2i& pos);
    void set_tile_resource(const godot::Vector2i& pos, ResourceType type, int count);

    void add_player(const Player& player);
    Player* get_player(int id);
    int get_tile_count() const;
    int get_player_count() const;
    void move_player(int id, const godot::Vector2i& new_pos);
    godot::Vector2i get_map_dimensions() const;

private:
    std::unordered_map<godot::Vector2i, Tile, Vector2iHash> tiles_;
    std::unordered_map<int, std::unique_ptr<Player>> players_;
};

}
