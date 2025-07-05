#include <algorithm>
#include "world.h"

using namespace zappy;
using namespace godot;

void World::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_tile_count"), &World::get_tile_count);
    ClassDB::bind_method(D_METHOD("get_player_count"), &World::get_player_count);
    ClassDB::bind_method(D_METHOD("get_map_dimensions"), &World::get_map_dimensions);
}

int World::get_tile_count() const {
    return tiles_.size();
}

int World::get_player_count() const {
    return players_.size();
}

Vector2i World::get_map_dimensions() const {
    Vector2i max(0, 0);
    for (const auto& [pos, tile] : tiles_) {
        max.x = std::max(max.x, pos.x);
        max.y = std::max(max.y, pos.y);
    }
    return max + Vector2i(1, 1);
}


Tile* World::get_tile(const Vector2i& pos) {
    return &tiles_[pos];  // creates if missing
}

void World::set_tile_resource(const Vector2i& pos, ResourceType type, int count) {
    Tile* tile = get_tile(pos);
    tile->set_resource(type, count);
}

void World::add_player(const Player& player) {
    if (players_.count(player.get_id())) return;

    auto copy = std::make_unique<Player>(player);
    get_tile(player.get_position())->add_player(copy.get());
    players_[player.get_id()] = std::move(copy);
}


Player* World::get_player(int id) {
    auto it = players_.find(id);
    return (it != players_.end()) ? it->second.get() : nullptr;
}

void World::move_player(int id, const Vector2i& new_pos) {
    Player* player = get_player(id);
    if (!player) return;

    Vector2i old_pos = player->get_position();
    if (old_pos != new_pos) {
        get_tile(old_pos)->remove_player(player);
        get_tile(new_pos)->add_player(player);
        player->set_position(new_pos);
    }
}
