#include "physics.h"
#include "../config/config.h"

void applyPhysics(Point *points, size_t point_amount)
{
    for (size_t i = 0; i < point_amount; i++)
    {
        // Applying physics for every particle
        Point *point_aux = (points + i);

        apply_colision(point_aux, points, point_amount, i);
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


// Need to fix this function
void apply_colision(Point *point1, Point *points, size_t point_amount, size_t current_index)
{
    float inverse_point1_mass = 1 / point1->mass;
    for (size_t j = current_index + 1; j < point_amount; j++)
    {
        Point *point2 = (points + j);
        float inverse_point2_mass = 1 / point2->mass;

        float combined_radius_square = ((point1->diameter / 2) + (point2->diameter / 2)) * ((point1->diameter / 2) + (point2->diameter / 2));
        float x_distance_square = (point1->x - point2->x) * (point1->x - point2->x);
        float y_distance_square = (point1->y - point2->y) * (point1->y - point2->y);
        if (combined_radius_square < (x_distance_square + y_distance_square))
        {
            continue;
        }

        float total_mass = point1->mass + point2->mass;
        float total_vx = point1->vx + point2->vx;
        float total_vy = point1->vy + point2->vy;

        point1->vx = (total_mass * total_vx - point2->mass * point2->vx) * inverse_point1_mass;
        point1->vy = (total_mass * total_vy - point2->mass * point2->vy) * inverse_point1_mass;

        point2->vx = (total_mass * total_vx - point1->mass * point1->vx) * inverse_point2_mass;
        point2->vy = (total_mass * total_vy - point1->mass * point1->vy) * inverse_point2_mass;
    }
}