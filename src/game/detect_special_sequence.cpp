#include "game/line_sequence.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::detect_special_sequence(LineSequence* data)
{
    // TODO: implement


    if(log_sequences_to_stdout) {
        int number = data - &line_sequences[0];
        cout << "Sequence " << number
             << " size: " << data->lines.size() << endl;
    }

}

