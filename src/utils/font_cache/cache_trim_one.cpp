#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"
#include <SDL2/SDL_timer.h>


void utils::cache_trim_one(FontCache* cache)
{
    auto itr = cache->entries.begin();
    auto target = itr;

    while(++itr != cache->entries.end()) {
        if(itr->priority < target->priority) {
            target = itr;
            continue;
        }
        if(itr->priority > target->priority)
            continue;

        auto now = SDL_GetTicks();
        auto time_itr = now - itr->last_use;
        auto time_target = now - target->last_use;
        if(time_itr > time_target) {
            target = itr;
            continue;
        }
    }

    auto entry = *itr;
    cache->entries.erase(itr);
    cache_destroy_entry(&entry);
}

#endif // USE_SDL2_TTF
