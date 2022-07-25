#include "core/core.hpp"
#include "game/game.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>

SDL_Window* core::window = nullptr;
SDL_Renderer* core::renderer = nullptr;

static bool running = false;


void core::run()
{
    running = true;
    u64 last = SDL_GetPerformanceCounter();
    u64 freq = SDL_GetPerformanceFrequency();
    float buffer = 0;
    
    while(running) {
        u64 now = SDL_GetPerformanceCounter();
        buffer += now - last;
        u32 raw = buffer * 1000 / freq;
        last = now;

        if(raw > 1) {
            core::poll_events();
            game::tick(raw);
            buffer -= raw * freq / 1000;
        }

        game::render();
    }
}

void core::stop()
{
    running = false;
}


void core::poll_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        switch(ev.type) {
        case SDL_MOUSEMOTION:
            game::handle_event(ev.motion);
            break;

        case SDL_MOUSEWHEEL:
            game::handle_event(ev.wheel);
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            game::handle_event(ev.key);
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            game::handle_event(ev.button);
            break;

        case SDL_DROPFILE:
        case SDL_DROPTEXT:
        case SDL_DROPBEGIN:
        case SDL_DROPCOMPLETE:
            game::handle_event(ev.drop);
            break;

        case SDL_QUIT:
            core::stop();
            break;
        }
    }
}
