#ifndef INCLUDE_PI_HPP
#define INCLUDE_PI_HPP

#include <cmath>

inline double pi()
{
    static double _pi = std::atan2(0.0, -1.0);
    return _pi;
}

inline double pi_f()
{
    static float _pi = std::atan2(0.0f, -1.0f);
    return _pi;
}

#endif // INCLUDE_PI_HPP
