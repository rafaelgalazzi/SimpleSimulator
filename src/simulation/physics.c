#include "physics.h"

void applyPhysics(Point *points)
{
    if (points->x > 1000)
    {
        points->vx = -points->vx;
    }

    if (points->x < 0)
    {
        points->vx = -points->vx;
    }

    points->x += points->vx;
}