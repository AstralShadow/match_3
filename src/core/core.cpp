#include "core/core.hpp"
#include "core/scene.hpp"
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
            poll_events();
            scene_tick(raw);
            buffer -= raw * freq / 1000;
        }

        scene_render();
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

        case SDL_KEYDOWN:
            scene_keydown(ev.key);
            break;
        case SDL_KEYUP:
            scene_keyup(ev.key);
            break;

        case SDL_MOUSEMOTION:
            scene_mouse_motion(ev.motion);
            break;

        case SDL_MOUSEWHEEL:
            scene_mouse_wheel(ev.wheel);
            break;

        case SDL_MOUSEBUTTONDOWN:
            scene_mousedown(ev.button);
            break;

        case SDL_MOUSEBUTTONUP:
            scene_mouseup(ev.button);
            break;

        /*
        case SDL_DROPFILE:
        case SDL_DROPTEXT:
        case SDL_DROPBEGIN:
        case SDL_DROPCOMPLETE:
            game::handle_event(ev.drop);
            break;
        */

        case SDL_QUIT:
            core::stop();
            break;
        }
    }
}
