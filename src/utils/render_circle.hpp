#ifndef INCLUDE_RENDER_CIRCLE_HPP
#define INCLUDE_RENDER_CIRCLE_HPP

#include "utils/point.hpp"

struct SDL_Renderer;


/** Uses Wikipedia:
 * https://wikipedia.org/wiki/Midpoint_circle_algorithm
 */
void render_fill_circle(SDL_Renderer*,
                        Point pos, int radius);
void render_draw_circle(SDL_Renderer*,
                        Point pos, int radius,
                        int line_width = 1);

#endif // INCLUDE_RENDER_CIRCLE_HPP
