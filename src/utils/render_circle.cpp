#include "render_circle.hpp"
#include <SDL2/SDL.h>

void render_fill_circle(SDL_Renderer* rnd,
                        Point pos, int r)
{
    Point points[8];
    int x = 0, y = r;
    int e = 3 - 2 * r;

    while(y >= x)
    {
        points[0].x = points[2].x = pos.x + x;
        points[1].x = points[3].x = pos.x - x;
        points[0].y = points[1].y = pos.y + y;
        points[2].y = points[3].y = pos.y - y;
        points[4].x = points[6].x = pos.x + y;
        points[5].x = points[7].x = pos.x - y;
        points[4].y = points[5].y = pos.y + x;
        points[6].y = points[7].y = pos.y - x;

        SDL_RenderDrawLines(rnd, &points[0], 2);
        SDL_RenderDrawLines(rnd, &points[2], 2);
        SDL_RenderDrawLines(rnd, &points[4], 2);
        SDL_RenderDrawLines(rnd, &points[6], 2);

        if(e > 0)
        {
            y--;
            e += 2 * (5 - 2*y + 2*x);
        }
        else
        {
            e += 2 * (3 + 2*x);
        }
        x++;
    }
}


void render_draw_circle_pixel(SDL_Renderer* rnd,
                              Point pos,
                              int x, int y,
                              int line_w)
{
    Point points[8];

    x -= line_w / 2;
    y -= line_w / 2;

    for(int x1 = 0; x1 < line_w; x1++)
    for(int y1 = 0; y1 < line_w; y1++)
    {
        points[0].x = points[2].x = pos.x + x + x1;
        points[1].x = points[3].x = pos.x - x - x1;
        points[0].y = points[1].y = pos.y + y + y1;
        points[2].y = points[3].y = pos.y - y - y1;
        points[4].x = points[6].x = pos.x + y + y1;
        points[5].x = points[7].x = pos.x - y - y1;
        points[4].y = points[5].y = pos.y + x + x1;
        points[6].y = points[7].y = pos.y - x - x1;

        SDL_RenderDrawPoints(rnd, points, 8);
    }
}

void render_draw_circle(SDL_Renderer* rnd,
                        Point pos, int r,
                        int line_width)
{
    int x = 0, y = r;
    int e = 3 - 2 * r;

    while(y >= x)
    {
        render_draw_circle_pixel
            (rnd, pos, x, y, line_width);

        if(e > 0)
        {
            y--;
            e += 2 * (5 - 2*y + 2*x);
        }
        else
        {
            e += 2 * (3 + 2*x);
        }
        x++;
    }
}

