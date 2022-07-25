#include "core/init.hpp"
#include "core/core.hpp"
#include "core/version.hpp"

#include <iostream>

using std::cout;
using std::endl;


int main(int argc, char** argv)
{
    cout << "Initializing..." << endl;
    core::init(argc, argv);

    cout << "Running "
         << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.'
         << VERSION_MINOR << endl;

    core::run();

    cout << "Closing "
         << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.'
         << VERSION_MINOR << endl;

    core::deinit();

    return 0;
}

