#include "net/message_parser.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace zappy;

void MessageParser::parse_message(const godot::String& msg, zappy::World* world) {
    PackedStringArray parts = msg.split(" ");
    if (parts.is_empty()) return;

    String cmd = parts[0];

    if (cmd == "msz") {
        if (parts.size() != 3) return;
        int width = parts[1].to_int();
        int height = parts[2].to_int();
        UtilityFunctions::print(vformat("Map size: %d x %d", width, height));
        // Tile t;
        // t.set_position(godot::Vector2(width, height));
        // TODO: World::set_size(width, height);
    }
    else if (cmd == "sgt") {
        if (parts.size() != 2) return;
        int tick = parts[1].to_int();
        UtilityFunctions::print(vformat("Tick rate: %d", tick));
    }
    else if (cmd == "pnw") {
        if (parts.size() < 7) return; // At minimum must have 7 tokens

        int id = parts[1].to_int();
        int x = parts[2].to_int();
        int y = parts[3].to_int();
        int orientation = parts[4].to_int();
        int level = parts[5].to_int();

        // Team name is everything after index 6 (parts[6..])
        String team_name;
        for (int i = 6; i < parts.size(); ++i) {
            team_name += parts[i];
            if (i < parts.size() - 1)
                team_name += " ";
        }

        UtilityFunctions::print(vformat("Player %d at (%d, %d), orientation %d, level %d, team: %s",
            id, x, y, orientation, level, team_name));
        
        Player parsed(id, Vector2i(x, y));
        parsed.set_orientation(orientation);
        parsed.set_level(level);
        parsed.set_team_name(team_name);
        world->add_player(parsed);
    }
    else if (cmd == "tna") {
        if (parts.size() != 2) return;
        UtilityFunctions::print(vformat("Team name: %s", parts[1]));
    }
    else if (cmd == "bct") {
        if (parts.size() != 10) return;
        int x = parts[1].to_int();
        int y = parts[2].to_int();
        Vector2i pos(x, y);

        for (int i = 0; i < 7; ++i) {
            ResourceType type = static_cast<ResourceType>(i);
            int count = parts[3 + i].to_int();
            world->set_tile_resource(pos, type, count);
        }
        // UtilityFunctions::print(vformat("Tile update at (%d, %d)", x, y));
    }
    else {
        UtilityFunctions::printerr("Unknown message: ", msg);
    }
}
