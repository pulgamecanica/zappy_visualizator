#pragma once

#include <array>
#include <string>
#include <godot_cpp/variant/vector2i.hpp>
#include "resource_type.h"

namespace zappy {

enum class Orientation {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

class Player {
public:
    Player(int id, godot::Vector2i start_pos);

    int get_id() const;
    godot::Vector2i get_position() const;
    void set_position(godot::Vector2i new_pos);

    void set_orientation(int o);
    void set_orientation(Orientation o);
    Orientation get_orientation() const;

    void set_level(int level);
    int get_level() const;

    void set_team_name(const std::string& name);
    const std::string& get_team_name() const;

    void add_resource(ResourceType type, int count);
    int get_resource(ResourceType type) const;

private:
    int id_;
    godot::Vector2i position_;
    Orientation orientation_ = Orientation::NORTH;
    int level_ = 1;
    std::string team_name_;

    std::array<int, NUM_RESOURCES> inventory_;
};

}
