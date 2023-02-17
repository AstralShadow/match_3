#ifndef INCLUDE_CORE_HOOKS_HPP
#define INCLUDE_CORE_HOOKS_HPP

#include "utils/types.hpp"

struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;


namespace core
{

    void init(int argc, char** argv, ...);
    void deinit(...);
    void tick(u32 ms, ...);
    void render(...);

    void keydown(SDL_KeyboardEvent& ev, ...);
    void keyup(SDL_KeyboardEvent& ev, ...);

    void mouse_motion(SDL_MouseMotionEvent& ev, ...);
    void mouse_wheel(SDL_MouseWheelEvent& ev, ...);
    void mouseup(SDL_MouseButtonEvent& ev, ...);
    void mousedown(SDL_MouseButtonEvent& ev, ...);


    template<typename T>
    void _init(int argc, char** argv, T nul = nullptr)
    {
        init(argc, argv, nul);
    }

    template<typename T>
    void _deinit(T nul = nullptr)
    {
        deinit(nul);
    }

    template<typename T>
    void _tick(u32 ms, T nul = nullptr)
    {
        tick(ms, nul);
    }

    template<typename T>
    void _render(T nul = nullptr)
    {
        render(nul);
    }


    template<typename T>
    void _keydown(SDL_KeyboardEvent& ev,
                  T nul = nullptr)
    {
        keydown(ev, nul);
    }

    template<typename T>
    void _keyup(SDL_KeyboardEvent& ev,
                T nul = nullptr)
    {
        keyup(ev, nul);
    }


    template<typename T>
    void _mouse_motion(SDL_MouseMotionEvent& ev,
                      T nul = nullptr)
    {
        mouse_motion(ev, nul);
    }

    template<typename T>
    void _mouse_wheel(SDL_MouseWheelEvent& ev,
                     T nul = nullptr)
    {
        mouse_wheel(ev, nul);
    }

    template<typename T>
    void _mouseup(SDL_MouseButtonEvent& ev,
                  T nul = nullptr)
    {
        mouseup(ev, nul);
    }

    template<typename T>
    void _mousedown(SDL_MouseButtonEvent& ev,
                    T nul = nullptr)
    {
        mousedown(ev, nul);
    }

}

#endif // INCLUDE_CORE_HOOKS_HPP
