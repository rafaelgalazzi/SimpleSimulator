#include "entity.h"

Point create_point(float x, float y, float vx, float vy, float mass, float diameter, float color[3])
{
    return (Point){
        .x = x,
        .y = y,
        .vx = vx,
        .vy = vy,
        .mass = mass,
        .diameter = diameter,
        .color = {color[0],
                  color[1],
                  color[2]}};
}