#pragma once

namespace zappy {

enum class ResourceType {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    COUNT
};

inline constexpr int NUM_RESOURCES = static_cast<int>(ResourceType::COUNT);

}
