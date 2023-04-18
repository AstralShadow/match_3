#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"


void utils::destroy_cache(FontCache* cache)
{
    cache_clear(cache);
    delete cache;
}

#endif // USE_SDL2_TTF
