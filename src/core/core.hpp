#ifndef INCLUDE_CORE_HPP
#define INCLUDE_CORE_HPP

#include "core/version.hpp"
#include "core/config.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace core
{
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    void run();
    void stop();

    void poll_events();
}

#endif // INCLUDE_CORE_HPP
