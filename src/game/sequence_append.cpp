#include "game/line_sequence.hpp"

namespace game
{
    LineSequence line_sequences[sequences_count];
    vector<Line> chain_reactions;
}


void game::sequence_append(Line const& line,
                           LineSequence* sequence)
{
    if(sequence) {
        sequence->lines.push_back(line);

        // TODO: Handle chain size
        chain_reactions.clear();

        detect_special_sequence(sequence);
    } else {
        chain_reactions.push_back(line);

        for(u32 i = 0; i < sequences_count; ++i)
            detect_special_sequence(&line_sequences[i]);
    }
}

