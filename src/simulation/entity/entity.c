#include "entity.h"
#include "../config/config.h"

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

float randomRange(float min, float max)
{
    return min + (float)rand() / 0x7fff * (max - min);
}

void create_many_points(Point *points, size_t point_amount)
{
    for (size_t i = 0; i < point_amount; i++)
    {
        float half_x_screen = SCREEN_WIDTH / 2;
        float half_y_screen = SCREEN_HEIGHT / 2;
        float x = randomRange(-half_x_screen, half_x_screen);
        float y = randomRange(-half_y_screen, half_y_screen);
        float vx = randomRange(-1.0f, 1.0f);
        float vy = randomRange(-1.0f, 1.0f);
        float mass = 1.0f;
        float diameter = 1.0f;

        float color[3] = {
            1.0f,
            1.0f,
            1.0f,
        };

        *(points + i) = create_point(x, y, vx, vy, mass, diameter, color);
    }
}