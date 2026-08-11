#include "physics.h"
#include "../config/config.h"

void applyPhysics(Point *points, size_t point_amount)
{
    for (size_t i = 0; i < point_amount; i++)
    {
        // Applying physics for every particle
        Point *point_aux = (points + i);

        applyBoundaries(point_aux);
        updatePosition(point_aux);
    }
}

void updatePosition(Point *point)
{
    point->x += point->vx;
    point->y -= point->vy; // Subtract because the increasing in Y goes to the bottom
}

void applyBoundaries(Point *point)
{
    if (point->x > (SCREEN_WIDTH / 2) || point->x < (-SCREEN_WIDTH / 2))
    {
        point->vx = -point->vx;
    }

    if (point->y > (SCREEN_HEIGHT / 2) || point->y < (-SCREEN_HEIGHT / 2))
    {
        point->vy = -point->vy;
    }
}