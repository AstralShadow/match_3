#include "game/move_queue.hpp"
#include "game/tile_lines.hpp"
#include "game/board.hpp"


void game::process_moves(int ms)
{
    float time = ms * 1.0f / animation_duration;
    begin_next_move();

    /* Active Moves */
    auto itr = active_moves.begin();
    while(itr != active_moves.end()) {
        itr->second += time;
        if(itr->second >= 1) {
            finish_move(itr->first);
            itr = active_moves
                .erase(itr);
        } else ++itr;
    }

    /* Cancelled Moves */
    itr = failed_moves.begin();
    while(itr != failed_moves.end()) {
        itr->second += time;
        if(itr->second < 0) {
            itr = failed_moves
                .erase(itr);
        } else ++itr;
    }
}

void game::begin_next_move()
{
    if(input_queue.size() == 0)
        return;
    auto next = input_queue.front();
    validate_move(next);
    auto target = next.first;
    auto destination = next.second;
    if(target.x == destination.x)
        if(target.y == destination.y) {
            input_queue.pop();
            return;
        }


    if(is_tile_in_use(target))
        return;
    if(is_tile_in_use(destination))
        return;

    active_moves[next] = 0;
    input_queue.pop();
}

void game::finish_move(move_t move)
{
    auto src = move.first;
    auto dst = move.second;
    auto t1 = get_tile(src.x, src.y);
    auto t2 = get_tile(dst.x, dst.y);
    std::swap(*t1, *t2);

    detect_lines(src);
    detect_lines(dst);

    // check for pairs

}


bool operator < (const Point a,
                 const Point b)
{
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}
