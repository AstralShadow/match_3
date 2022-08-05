#include "core/scene.hpp"

#include "game/game.hpp"


void core::register_scenes()
{
    core::scene<game::scene_uid>("game");
    core::set_scene("game");
}


