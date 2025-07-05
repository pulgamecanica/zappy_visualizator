#include "player.h"

using namespace zappy;
using namespace godot;

Player::Player(int id, godot::Vector2i start_pos)
    : id_(id), position_(start_pos), level_(1), orientation_(Orientation::NORTH), inventory_{} {
    inventory_.fill(0);
    add_resource(ResourceType::FOOD, 10);
}

int Player::get_id() const {
    return id_;
}

Vector2i Player::get_position() const {
    return position_;
}

void Player::set_position(Vector2i new_pos) {
    position_ = new_pos;
}

void Player::set_orientation(int o) {
    set_orientation(static_cast<Orientation>(o));
}

void Player::set_orientation(Orientation o) {
    orientation_ = o;
}

Orientation Player::get_orientation() const {
    return orientation_;
}

void Player::set_level(int level) {
    level_ = level;
}

int Player::get_level() const {
    return level_;
}

void Player::set_team_name(const std::string& name) {
    team_name_ = name;
}

const std::string& Player::get_team_name() const {
    return team_name_;
}

void Player::add_resource(ResourceType type, int count) {
    std::size_t index = static_cast<std::size_t>(type);
    if (index >= 0 && index < NUM_RESOURCES) {
        inventory_[index] += count;
    }
}

int Player::get_resource(ResourceType type) const {
    std::size_t index = static_cast<std::size_t>(type);
    if (index >= 0 && index < NUM_RESOURCES) {
        return inventory_[index];
    }
    return 0;
}
