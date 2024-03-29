#ifndef INCLUDE_GAME_MOVE_QUEUE_HPP
#define INCLUDE_GAME_MOVE_QUEUE_HPP

#include <queue>
#include <map>
#include "utils/point.hpp"
#include "game/line_sequence.hpp"

namespace game
{
    using std::pair;
    using std::queue;
    using std::map;

    struct move_t
    {
        Point first, second;
        LineSequence* sequence = nullptr;
    };

    extern queue<move_t> input_queue;

    // stores active moves and animation
    //  progress from 0 to 1
    extern map<move_t, float> // [0,1]
        active_moves;
    // Stores moves that are
    //  reverted because of
    //  not making a match
    extern map<move_t, float> // [1,0]
        failed_moves;


    void equeue_move(move_t);

    // Converts a move to the
    //  closest valid simple move
    void validate_move(move_t&);

    void process_moves(int);
    void begin_next_move();
    void finish_move(move_t);
    void finish_failed_move(move_t);

    bool is_tile_moving(Point);

    bool operator < (const move_t a,
                     const move_t b);
};

bool operator < (const Point a,
                 const Point b);


#endif // INCLUDE_GAME_MOVE_QUEUE_HPP
