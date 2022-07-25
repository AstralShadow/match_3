#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include "utils/types.hpp"

struct SDL_KeyboardEvent;

namespace game
{
    void init(int, char**);

    void tick(u32 ms);

    void render();

    template<typename T>
    extern void handle_event(T&);
}

#endif // INCLUDE_GAME_HPP
