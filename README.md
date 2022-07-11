# Match 3 in a row
Nameless clone of a very popular group of games.


# Building
Dependencies:
GCC (or other C++11 compatable compiler),
make,
libsdl2

If you want to change the compiler or the compile
flags, you can edit the makefile.


To build and run the game:

    git clone https://github.com/AstralShadow/match_3.git
    cd match_3
    make -j$(nproc)
    make run


## Windows
The game is expected to work relatively fine under
Windows. I haven't really tested it yet, and you
will need to setup your compiler and SDL2 by yourself

I'll eventually use CMake later and make the build
process easier for any windows users.


# Controls
Use the mouse to click & drag tiles
or use the WASD/Arrow keys to move
and the space key to select.


# Scoring
Currently you can see your score as 6 different bars
for every color. The bars reset on overflow and do
pretty much nothing yet.

You can also see your score in stdout if you run
the application from a terminal.

The current scoring system relies heavily on the count
of the tiles you remove. Some tiles give bonus points.
