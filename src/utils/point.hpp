#ifndef INCLUDE_POINT_HPP
#define INCLUDE_POINT_HPP

#include <SDL2/SDL_rect.h>

typedef SDL_Point Point;
typedef SDL_FPoint FPoint;

constexpr bool operator == (Point const& a,
                            Point const& b)
{
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator != (Point const& a,
                            Point const& b)
{
    return !(a == b);
}

#endif // INCLUDE_POINT_HPP
