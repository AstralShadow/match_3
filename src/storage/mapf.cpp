#include "utils.hpp"
#include <limits>

/* These functions will most likely introduce
 *  inaccuracity and changes when storing.    */

u32 mapf(float value, float min, float max)
{
    u32 u32_max = std::numeric_limits<u32>::max();

    double distance = max - min;
    value -= min;
    double data = value / distance;
    return static_cast<u32>(data * u32_max);
}

float unmapf(u32 value, float min, float max)
{
    u32 u32_max = std::numeric_limits<u32>::max();

    double range = max - min;
    double distance = range * value / u32_max;
    double data = distance + min;
    return static_cast<float>(data);
}

