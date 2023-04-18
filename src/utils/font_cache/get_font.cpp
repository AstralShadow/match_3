#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>


TTF_Font* utils::get_font(FontCache* cache,
                          fs::path path, int size,
                          int priority)
{
    auto* entry = find_font(cache, path, size);

    if(entry) {
        if(entry->priority < priority)
            entry->priority = priority;
        entry->last_use = SDL_GetTicks();
    } else {
        entry = load_font(cache, path, size, priority);
        if(!entry)
            return nullptr;
    }

    return entry->font;
}

#endif // USE_SDL2_TTF
