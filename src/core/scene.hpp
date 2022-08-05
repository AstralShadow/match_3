#ifndef INCLUDE_SCENE_HPP
#define INCLUDE_SCENE_HPP

#include "core/core.hpp"
#include "core/hooks.hpp"
#include "utils/types.hpp"
#include <string>
#include <vector>
#include <functional>

using std::string;
using std::vector;
using std::function;


namespace core
{
    struct SceneData
    {
        string name;
        function<void(int, char**)> init;
        function<void()> deinit;
        function<void(u32)> tick;
        function<void()> render;

        function<void(SDL_KeyboardEvent&)> keydown;
        function<void(SDL_KeyboardEvent&)> keyup;

        function<void(SDL_MouseMotionEvent&)> motion;
        function<void(SDL_MouseWheelEvent&)> wheel;

        function<void(SDL_MouseButtonEvent&)> mousedown;
        function<void(SDL_MouseButtonEvent&)> mouseup;
    };

    extern vector<SceneData> scenes;


    template<typename T>
    void scene(string name, T nul = nullptr)
    {
        using namespace std::placeholders;

        core::SceneData scene;
        scene.name = name;

        scene.init = std::bind(_init<T>, _1, _2, nul);
        scene.deinit = std::bind(_deinit<T>, nul);
        scene.tick = std::bind(_tick<T>, _1, nul);
        scene.render = std::bind(_render<T>, nul);

        scene.keyup = std::bind(_keyup<T>, _1, nul);
        scene.keydown = std::bind(_keydown<T>, _1, nul);

        scene.wheel = std::bind(_mouse_wheel<T>, _1, nul);
        scene.motion = std::bind(_mouse_motion<T>, _1, nul);
        scene.mouseup = std::bind(_mouseup<T>, _1, nul);
        scene.mousedown = std::bind(_mousedown<T>, _1, nul);

        core::scenes.push_back(scene);
    }
}

#endif // INCLUDE_SCENE_HPP
