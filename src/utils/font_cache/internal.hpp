#ifndef INCLUDE_INTERNAL_HPP
#define INCLUDE_INTERNAL_HPP

#include "utils/font_cache.hpp"

using utils::FontCache;
using utils::FontCacheEntry;

// TODO: possibly use binary search and sort by proper insertion rather than appending.

namespace utils
{
    void cache_destroy_entry(FontCacheEntry* entry);

    // Clears the entry with least priority that
    //  hasn't been accessed from longest time.
    void cache_trim_one(FontCache* cache);

    FontCacheEntry* find_font(FontCache*, fs::path, int size);
    FontCacheEntry* load_font(FontCache*, fs::path, int size, int priority);
}

#endif // INCLUDE_INTERNAL_HPP
