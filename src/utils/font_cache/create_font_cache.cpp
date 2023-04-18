#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"


FontCache* utils::create_font_cache()
{
    return new FontCache();
}

#endif // USE_SDL2_TTF
