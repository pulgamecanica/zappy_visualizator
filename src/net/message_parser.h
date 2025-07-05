#pragma once

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>
#include "core/world.h"

namespace zappy {

class MessageParser {
public:
    static void parse_message(const godot::String& msg, zappy::World* world);
};

}