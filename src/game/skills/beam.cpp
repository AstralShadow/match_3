#include "game/skills/beam.hpp"
#include "game/board.hpp"
#include "config/skills.hpp"

using game::Beam;
static int break_duration = config::beam_break_duration;
static int motion_delay = config::beam_motion_delay;

static Point validate_direction(Point _direction);


Beam::Beam(Point _pos, Point _direction) :
    pos(_pos),
    direction(validate_direction(_direction))
{
    find_targets();
}

static Point validate_direction(Point _direction)
{
    Point direction {0, 0};
    if(_direction.x < 0)
        direction.x = -1;
    if(_direction.x > 0)
        direction.x = 1;

    if(_direction.y < 0)
        direction.y = -1;
    if(_direction.y > 0)
        direction.y = 1;

    if(direction.x == 0 && direction.y == 0)
        direction.x = 1;

    return direction;
}


void Beam::find_targets()
{
    if(!is_tile_in_use(pos)) {
        tiles.push_back(pos);
        tile_progress.push_back(0);
    }

    int i = 1;
    Point next = pos + direction;
    while(get_tile(next)) {
        if(!is_tile_in_use(next, CHK_IGNORE_LOCKED)) {
            tiles.push_back(next);
            tile_progress.push_back(-motion_delay * i);
        }
        i++;
        next = next + direction;
    }

    i = 1;
    next = pos - direction;
    while(get_tile(next)) {
        if(!is_tile_in_use(next, CHK_IGNORE_LOCKED)) {
            tiles.push_back(next);
            tile_progress.push_back(-motion_delay * i);
        }
        i++;
        next = next - direction;
    }
}


void Beam::tick(u32 time)
{
    for(u32 i = 0; i < tiles.size(); ++i) {
        auto const& tile = tiles[i];
        int& p = tile_progress[i];
        int p2 = p + static_cast<int>(time);

        // Skip tiles that are busy
        if(p < 0 && p2 >= 0)
        if(is_tile_in_use(tile, CHK_IGNORE_LOCKED)) {
            p += time + break_duration;
            continue;
        }

        // Remove tiles that finished their animation
        if(p < break_duration && p2 >= break_duration)
            remove_tile(tiles[i]);

        p = p2;
    }
}

bool Beam::is_locked(Point tile)
{
    for(u32 i = 0; i < tiles.size(); ++i) {
        if(tiles[i] != tile)
            continue;

        int p = tile_progress[i];
        // TODO decide on one of these return statements
        return p < break_duration;
        //return (p >= 0 && p < break_duration);
    }

    return false;
}

bool Beam::is_done()
{
    for(int p : tile_progress) {
        if(p < break_duration)
            return false;
    }

    return true;
}


bool Beam::apply_tile_anim(Point tile, SDL_Rect& output)
{
    for(u32 i = 0; i < tiles.size(); ++i) {
        if(tiles[i] != tile)
            continue;

        int p = tile_progress[i];
        if(p < 0 || p >= break_duration)
            return false;

        float shrink = (p * 1.0f / break_duration);
        int shrink_px_x = output.w * shrink / 2;
        int shrink_px_y = output.h * shrink / 2;
        output.x += shrink_px_x;
        output.y += shrink_px_y;
        output.w -= shrink_px_x * 2;
        output.h -= shrink_px_y * 2;

        return true;
    }

    return false;
}

