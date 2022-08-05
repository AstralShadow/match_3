#include "core/init.hpp"
#include "core/scene.hpp"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

namespace core
{
    vector<SceneData> scenes;
    u32 current = 0;
}


void core::init_scenes(int argc, char** argv)
{
    for(auto scene : scenes) {
        if(scene.init)
            scene.init(argc, argv);
    }
    if(scenes.size() == 0)
        throw std::runtime_error("No scenes defined.");
}

void core::deinit_scenes()
{
    for(auto scene : scenes) {
        if(scene.deinit)
            scene.deinit();
    }
}


void core::set_scene(string name)
{
    for(u32 i = 0; i < scenes.size(); ++i) {
        if(scenes[i].name == name) {
            current = i;
            return;
        }
    }

    throw std::runtime_error
        ("Could not find scene: " + name);
}


void core::scene_tick(u32 time)
{
    auto& scene = scenes[current];
    if(scene.tick != nullptr)
        scene.tick(time);
}

void core::scene_render()
{
    auto& scene = scenes[current];
    if(scene.render != nullptr)
        scene.render();
}


void core::scene_keydown(SDL_KeyboardEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.keydown != nullptr)
        scene.keydown(ev);
}

void core::scene_keyup(SDL_KeyboardEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.keyup != nullptr)
        scene.keyup(ev);
}


void core::scene_mouse_motion(SDL_MouseMotionEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.motion!= nullptr)
        scene.motion(ev);
}

void core::scene_mouse_wheel(SDL_MouseWheelEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.wheel != nullptr)
        scene.wheel(ev);
}


void core::scene_mousedown(SDL_MouseButtonEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.mousedown != nullptr)
        scene.mousedown(ev);
}

void core::scene_mouseup(SDL_MouseButtonEvent& ev)
{
    auto& scene = scenes[current];
    if(scene.mouseup != nullptr)
        scene.mouseup(ev);
}
