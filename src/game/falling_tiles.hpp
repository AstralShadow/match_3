#ifndef INCLUDE_GAME_FALLING_TILES_HPP
#define INCLUDE_GAME_FALLING_TILES_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <vector>


namespace game
{
    using std::vector;

    struct FallingTiles
    {
        vector<Point> tiles;

        float progress = 0; // [0, 1]
        float age = 0; // [0, ..]
    };

    extern vector<FallingTiles> falling_tiles;


    bool is_tile_falling(Point pos);
    bool can_tile_fall(Point pos);

    void process_falling_tiles(int);
    void process_falling_tiles_progress(int);
    void process_falling_tiles_activation(int);

    void activate_falling_tiles();
    void finish_fall(FallingTiles);
}


#endif // INCLUDE_GAME_FALLING_TILES_HPP
