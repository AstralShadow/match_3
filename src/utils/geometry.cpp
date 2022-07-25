#include "geometry.hpp"

/**
 * Implementation based on Wikipedia:
 * https://en.wikipedia.org/wiki/Line-line_intersection
 */

bool segment_intersection(FPoint p1, FPoint p2,
                          FPoint p3, FPoint p4,
                          FPoint* p_out)
{
        float delta_x1 = p1.x - p2.x;
        float delta_y1 = p1.y - p2.y;
        float delta_x2 = p3.x - p4.x;
        float delta_y2 = p3.y - p4.y;

        float t = (p1.x - p3.x) * delta_y2 - (p1.y - p3.y) * delta_x2;
        float u = (p1.x - p3.x) * delta_y1 - (p1.y - p3.y) * delta_x1;
        float limit = delta_x1 * delta_y2 - delta_y1 * delta_x2;

        bool result = limit > 0
                ? (0 < t && t < limit && 0 < u && u < limit)
                : (limit < t && t < 0 && limit < u && u < 0);


        if(p_out && result)
        {
                p_out->x = p1.x - t * delta_x1 / limit;
                p_out->y = p1.y - t * delta_y1 / limit;
        }

        return result;
}
