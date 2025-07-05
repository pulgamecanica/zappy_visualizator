// #pragma once

// #include <godot_cpp/classes/object.hpp>
// #include <godot_cpp/variant/vector2i.hpp>
// #include <godot_cpp/variant/dictionary.hpp>
// #include <array>

// namespace zappy {

// enum class ResourceType {
//     FOOD = 0,
//     LINEMATE,
//     DERAUMERE,
//     SIBUR,
//     MENDIANE,
//     PHIRAS,
//     THYSTAME,
//     COUNT // internal use for array sizing
// };

// class Tile : public godot::Object {
//     GDCLASS(Tile, godot::Object)

// private:
//     godot::Vector2i grid_position;
//     std::array<int, static_cast<int>(ResourceType::COUNT)> resources;

// protected:
//     static void _bind_methods();

// public:
//     Tile();
//     ~Tile();

//     void set_position(const godot::Vector2i& pos);
//     godot::Vector2i get_position() const;

//     void set_resource_count(int type, int count);
//     int get_resource_count(int type) const;

//     void reset_resources();
//     godot::Dictionary get_all_resources() const;

//     godot::String to_string() const;
// };

// } // namespace zappy
