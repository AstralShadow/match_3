#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"
#include <SDL2/SDL_ttf.h>


void utils::cache_destroy_entry(FontCacheEntry* entry)
{
    TTF_CloseFont(entry->font);
}

#endif // USE_SDL2_TTF
