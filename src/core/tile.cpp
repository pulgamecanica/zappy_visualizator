#include "tile.h"
#include <algorithm>

using namespace zappy;

Tile::Tile() {
    resources_.fill(0);
}

void Tile::set_resource(ResourceType type, int count) {
    resources_[static_cast<int>(type)] = count;
}

int Tile::get_resource(ResourceType type) const {
    return resources_[static_cast<int>(type)];
}

const std::array<int, NUM_RESOURCES>& Tile::get_all_resources() const {
    return resources_;
}

void Tile::add_player(Player* player) {
    players_.push_back(player);
}

void Tile::remove_player(Player* player) {
    players_.erase(std::remove(players_.begin(), players_.end(), player), players_.end());
}

const std::vector<Player*>& Tile::get_players() const {
    return players_;
}
