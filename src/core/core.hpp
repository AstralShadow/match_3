#ifndef INCLUDE_CORE_HPP
#define INCLUDE_CORE_HPP

#include "utils/types.hpp"
#include "core/version.hpp"
#include "core/config.hpp"
#include <string>

struct SDL_Window;
struct SDL_Renderer;
using std::string;

struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;


namespace core
{
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    void run();
    void stop();

    void poll_events();

    void register_scenes();
    void set_scene(string name);
    void scene_tick(u32);
    void scene_render();

    void scene_keydown(SDL_KeyboardEvent&);
    void scene_keyup(SDL_KeyboardEvent&);
    
    void scene_mouse_motion(SDL_MouseMotionEvent&);
    void scene_mouse_wheel(SDL_MouseWheelEvent&);
    void scene_mouseup(SDL_MouseButtonEvent&);
    void scene_mousedown(SDL_MouseButtonEvent&);
}

#endif // INCLUDE_CORE_HPP
