#ifndef INCLUDE_GAME_COLORS_HPP
#define INCLUDE_GAME_COLORS_HPP

#include "utils/types.hpp"

namespace game
{
    struct Color {
        u8 r;
        u8 g;
        u8 b;
    };

    const Color colors[] = {
        //{  0,   0,   0},
        {255,   0,   0},
        {  0, 255,   0},
        {  0,   0, 255},
        {255, 255,   0},
        {  0, 255, 255},
        {255,   0, 255},
        //{255, 255, 255}
    };

    u8 random_color_index();
}

#endif // INCLUDE_GAME_COLORS_HPP
