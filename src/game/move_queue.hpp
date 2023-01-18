#ifndef INCLUDE_MOVE_QUEUE_HPP
#define INCLUDE_MOVE_QUEUE_HPP

#include <queue>
#include <map>
#include "utils/point.hpp"

namespace game
{
    using std::pair;
    using std::queue;
    using std::map;

    typedef pair<Point, Point> move_t;
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

    // Converts a move to the
    //  closest valid move
    void validate_move(move_t&);

    void process_moves(int);
    void begin_next_move();
    void finish_move(move_t);

    bool is_tile_in_use(Point);

};

bool operator < (const Point a,
                 const Point b);

#endif
