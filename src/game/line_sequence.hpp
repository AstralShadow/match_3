#ifndef INCLUDE_GAME_LINE_SEQUENCE_HPP
#define INCLUDE_GAME_LINE_SEQUENCE_HPP

#include "game/line.hpp"
#include "config/keyboard.hpp"
#include <vector>


namespace game
{
    using std::vector;

    struct LineSequence
    {
        vector<Line> lines;
    };

    // Last sequence is for mouse/touchscreen input
    const u32 sequences_count
        = config::max_kb_players + 1;

    extern LineSequence line_sequences[sequences_count];
    extern vector<Line> chain_reactions;


    void sequence_append(Line const&,
                         LineSequence* = nullptr);

    void detect_special_sequence(LineSequence*);

}

#endif // INCLUDE_GAME_LINE_SEQUENCE_HPP
