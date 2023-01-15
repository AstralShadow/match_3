#ifndef INCLUDE_MOVE_QUEUE_HPP
#define INCLUDE_MOVE_QUEUE_HPP

#include <queue>
#include "utils/point.hpp"

namespace game
{
    using std::pair;
    using std::queue;

    typedef pair<Point, Point> move_t;
    extern queue<move_t> move_queue;
};

#endif
