#pragma once

#include <array>
#include <vector>
#include "resource_type.h"

namespace zappy {

class Player;

class Tile {
public:
    Tile();

    void set_resource(ResourceType type, int count);
    int get_resource(ResourceType type) const;
    const std::array<int, NUM_RESOURCES>& get_all_resources() const;

    void add_player(Player* player);
    void remove_player(Player* player);
    const std::vector<Player*>& get_players() const;

private:
    std::array<int, NUM_RESOURCES> resources_;
    std::vector<Player*> players_;
};

}
