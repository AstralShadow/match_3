#include "game/line_sequence.hpp"
#include "game/skills/beam.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::detect_special_sequence(LineSequence* data)
{
    if(data->lines.size() < 1)
        return;

    auto const& last_line = data->lines.back();

    Point direction = last_line[0] - last_line[1];
    active_skills.push_back(std::make_unique
        <Beam>(last_line[0], direction)
    );
    data->lines.pop_back();

    // TODO: implement
    
    if(log_sequences_to_stdout) {
        int number = data - &line_sequences[0];
        cout << "Sequence " << number
             << " size: " << data->lines.size() << endl;
    }

}

