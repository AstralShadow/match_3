#include "game/line_animation.hpp"
#include "game/board.hpp"
#include "game/line_sequence.hpp"


void game::finish_line_animation(LineAnimationData* data)
{
    // TODO scoring

    sequence_append(data->line, data->sequence);

    for(Point pos : data->line)
        remove_tile(pos);
}

