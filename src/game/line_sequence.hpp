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
    const u32 sequences_count = 1 + config::max_kb_players;
    extern LineSequence line_sequences[sequences_count];
    extern vector<Line> chain_reactions;


    const bool log_sequences_to_stdout = false;


    void sequence_append(Line const&,
                         LineSequence* = nullptr);

    void detect_special_sequence(LineSequence*);

}

#endif // INCLUDE_GAME_LINE_SEQUENCE_HPP
