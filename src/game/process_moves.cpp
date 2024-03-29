#include "game/move_queue.hpp"
#include "game/line_animation.hpp"
#include "game/board.hpp"
#include "config/game.hpp"


void game::process_moves(int ms)
{
    float time = ms * 1.0f / config::move_duration;
    begin_next_move();

    /* Active Moves */
    auto itr = active_moves.begin();
    while(itr != active_moves.end()) {
        itr->second += time;
        if(itr->second >= 1) {
            auto move = itr->first;
            itr = active_moves.erase(itr);
            finish_move(move);
        } else ++itr;
    }

    /* Cancelled Moves */
    itr = failed_moves.begin();
    while(itr != failed_moves.end()) {
        itr->second -= time;
        if(itr->second < 0) {
            auto move = itr->first;
            itr = failed_moves.erase(itr);
            finish_failed_move(move);
        } else ++itr;
    }
}

void game::begin_next_move()
{
    if(input_queue.size() == 0)
        return;
    auto move = input_queue.front();
    validate_move(move);
    auto target = move.first;
    auto dest = move.second;
    if(target.x == dest.x)
        if(target.y == dest.y) {
            input_queue.pop();
            return;
        }

    if(is_tile_in_use(target) || is_tile_in_use(dest)) {
        if(config::requeue_waiting_moves)
            input_queue.push(input_queue.front());
        input_queue.pop();

        return;
    }

    active_moves[move] = 0;
    input_queue.pop();
}

void game::finish_move(move_t move)
{
    auto src = move.first;
    auto dst = move.second;
    auto t1 = get_tile(src.x, src.y);
    auto t2 = get_tile(dst.x, dst.y);
    std::swap(*t1, *t2);

    bool line = detect_lines(src, move.sequence);
    line = detect_lines(dst, move.sequence) || line;

    if(!config::permit_free_moves && !line) {
        std::swap(*t1, *t2);
        failed_moves[move] = 1;
    }
}

void game::finish_failed_move(move_t move)
{
    detect_lines(move.first);
    detect_lines(move.second);
}


bool game::operator < (const move_t a,
                       const move_t b)
{
    if(a.sequence != b.sequence)
        return a.sequence < b.sequence;

    if(a.first != b.first)
        return a.first < b.first;

    return a.second < b.second;
}

bool operator < (const Point a,
                 const Point b)
{
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

