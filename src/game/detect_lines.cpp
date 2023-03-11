#include "game/tile_lines.hpp"
#include "game/board.hpp"
#include "config/game.hpp"

using std::vector;
using std::size_t;


namespace game
{
    static bool check_direction(Point pos,
                                Point direction,
                                size_t min_count = 3);
}


bool game::detect_lines(Point pos)
{
    bool success = false;
    for(auto direction : {Point{0, 1}, {1, 0}})
        success = check_direction(pos, direction)
            || success;

    if(config::detect_diagonal_lines)
    for(auto direction : {Point{1, 1}, {1, -1}})
        success = check_direction(pos, direction)
            || success;

    return success;
}

bool game::check_direction(Point pos,
                           Point direction,
                           size_t min_count)
{
    vector<Point> line {pos};
    Tile* target = get_tile(pos);

    Point pos2 = pos;
    while(true) {
        pos2 = pos2 + direction;
        if(is_tile_in_use(pos2))
            break;

        Tile* other = get_tile(pos2);
        if(!other || !are_similar(target, other))
            break;

        line.push_back(pos2);
    }

    pos2 = pos;
    while(true) {
        pos2 = pos2 - direction;
        if(is_tile_in_use(pos2))
            break;

        Tile* other = get_tile(pos2);
        if(!other || !are_similar(target, other))
            break;

        line.push_back(pos2);
    }

    if(line.size() < min_count)
        return false;

    break_animation.push_back({line});
    return true;
}

