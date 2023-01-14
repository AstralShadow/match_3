#include "game/tile.hpp"
#include "game/colors.hpp"

using game::Tile;

Tile game::create_tile()
{
    Tile tile;
    tile.color = random_color_index();

    return tile;
}

