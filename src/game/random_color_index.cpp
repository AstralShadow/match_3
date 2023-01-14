#include "game/colors.hpp"
#include <random>

using uniform_int = std::uniform_int_distribution<>;


u8 game::random_color_index()
{
    static std::mt19937 generator(([](){
        std::random_device random_dev;
        return random_dev();
    })());
    static uniform_int distribution
        (0, sizeof colors / sizeof colors[0] - 1);

    return distribution(generator);
}
