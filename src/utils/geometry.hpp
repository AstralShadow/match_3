#ifndef INCLUDE_GEOMETRY_HPP
#define INCLUDE_GEOMETRY_HPP

#include <utils/point.hpp>

/**
 * Returns if two segments intersect.
 *
 * Puts the intersection point in *result.
 */
bool segment_intersection(FPoint p1, FPoint p2,
                          FPoint p3, FPoint p4,
                          FPoint* p_out = nullptr);

#endif // INCLUDE_GEOMETRY_HPP
