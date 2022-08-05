#include "core/init.hpp"
#include "core/scene.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


void core::init(int, char**, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unused init hook" << endl;
#endif
}

void core::deinit(...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unused deinit hook" << endl;
#endif
}

void core::tick(u32, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unused tick hook" << endl;
#endif
}

void core::render(...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unused render hook" << endl;
#endif
    SDL_RenderClear(core::renderer);
    SDL_RenderPresent(core::renderer);
}


void core::keydown(SDL_KeyboardEvent& ev, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unhandled keydown event." << endl;
#endif
    if(ev.keysym.sym == SDLK_q) {
        core::stop();
        cout << "Stopping because key is [Q]uit" << endl;
    }
}

void core::keyup(SDL_KeyboardEvent&, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unhandled keyup event." << endl;
#endif
}


void core::mouse_motion(SDL_MouseMotionEvent&, ...)
{
}

void core::mouse_wheel(SDL_MouseWheelEvent&, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unhandled mouse wheel event." << endl;
#endif
}

void core::mouseup(SDL_MouseButtonEvent&, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unhandled mouseup event." << endl;
#endif
}

void core::mousedown(SDL_MouseButtonEvent&, ...)
{
#ifdef VERBOSE_UNHANDLED_EVENTS
    cout << "Unhandled mousedown event." << endl;
#endif
}
