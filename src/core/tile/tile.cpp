// #include "tile.h"
// #include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/variant/utility_functions.hpp>

// using namespace godot;
// using namespace zappy;

// void Tile::_bind_methods() {
//     // No need to expose the setters since all management is dene via the server connection
//     // ClassDB::bind_method(D_METHOD("set_position", "pos"), &Tile::set_position);
//     ClassDB::bind_method(D_METHOD("get_position"), &Tile::get_position);

//     // ClassDB::bind_method(D_METHOD("set_resource_count", "type", "count"), &Tile::set_resource_count);
//     ClassDB::bind_method(D_METHOD("get_resource_count", "type"), &Tile::get_resource_count);

//     // ClassDB::bind_method(D_METHOD("reset_resources"), &Tile::reset_resources);
//     ClassDB::bind_method(D_METHOD("get_all_resources"), &Tile::get_all_resources);
//     ClassDB::bind_method(D_METHOD("to_string"), &Tile::to_string);
// }

// Tile::Tile() {
//     resources.fill(0);
// }

// Tile::~Tile() {}

// void Tile::set_position(const Vector2i& pos) {
//     grid_position = pos;
// }

// Vector2i Tile::get_position() const {
//     return grid_position;
// }

// void Tile::set_resource_count(int type, int count) {
//     if (type < 0 || type >= static_cast<int>(ResourceType::COUNT)) {
//         UtilityFunctions::push_error("Invalid resource type index: " + String::num_int64(type));
//         return;
//     }
//     resources[type] = count;
// }

// int Tile::get_resource_count(int type) const {
//     if (type < 0 || type >= static_cast<int>(ResourceType::COUNT)) {
//         UtilityFunctions::push_error("Invalid resource type index: " + String::num_int64(type));
//         return 0;
//     }
//     return resources[type];
// }

// void Tile::reset_resources() {
//     resources.fill(0);
// }

// Dictionary Tile::get_all_resources() const {
//     Dictionary dict;
//     for (int i = 0; i < static_cast<int>(ResourceType::COUNT); ++i) {
//         dict[i] = resources[i];
//     }
//     return dict;
// }

// String Tile::to_string() const {
//     String out = "[Tile ";
//     out += "(x=" + String::num_int64(grid_position.x) + ", y=" + String::num_int64(grid_position.y) + ") ";
//     out += "Resources: ";
//     for (int i = 0; i < static_cast<int>(ResourceType::COUNT); ++i) {
//         out += String::num_int64(resources[i]);
//         if (i < static_cast<int>(ResourceType::COUNT) - 1)
//             out += ", ";
//     }
//     out += "]";
//     return out;
// }
