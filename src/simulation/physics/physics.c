#include <math.h>
#include <omp.h>
#include "physics.h"
#include "../config/config.h"

void applyPhysics(Point *points, size_t point_amount, double *last_update_time)
{
    long long i;
    double time_now = glfwGetTime();
    double delta_time = time_now - *last_update_time;
    #pragma omp parallel for
    for (i = 0; i < point_amount; i++)
    {
        Point *point_aux = points + i;

        apply_colision(
            point_aux,
            points,
            point_amount,
            (size_t)i);

        applyBoundaries(point_aux);
        updatePosition(point_aux, &delta_time);
    }
    *last_update_time = time_now;
}

void updatePosition(Point *point, double *delta_time)
{

    point->x += point->vx * (float)(*delta_time);
    point->y -= point->vy * (float)(*delta_time); // Subtract because the increasing in Y goes to the bottom
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
    for (size_t j = current_index + 1; j < point_amount; j++)
    {
        Point *point2 = (points + j);

        float dx = point1->x - point2->x;
        float dy = point1->y - point2->y;
        float x_distance_square = dx * dx;
        float y_distance_square = dy * dy;
        float distSq = x_distance_square + y_distance_square;

        float r1 = point1->diameter / 2.0f;
        float r2 = point2->diameter / 2.0f;

        float combined_radius_square = (r1 + r2) * (r1 + r2);

        if (distSq < combined_radius_square)
        {
            float dist = sqrtf(distSq);
            float nx = dx / dist;
            float ny = dy / dist;

            float vn1 = point1->vx * nx + point1->vy * ny;
            float vn2 = point2->vx * nx + point2->vy * ny;

            float vt1x = point1->vx - vn1 * nx;
            float vt1y = point1->vy - vn1 * ny;

            float vt2x = point2->vx - vn2 * nx;
            float vt2y = point2->vy - vn2 * ny;

            float m1 = point1->mass;
            float m2 = point2->mass;
            float total_mass = m1 + m2;

            float new_vn1 = ((m1 - m2) * vn1 + 2.0f * m2 * vn2) / total_mass;
            float new_vn2 = ((m2 - m1) * vn2 + 2.0f * m1 * vn1) / total_mass;

            point1->vx = vt1x + new_vn1 * nx;
            point1->vy = vt1y + new_vn1 * ny;

            point2->vx = vt2x + new_vn2 * nx;
            point2->vy = vt2y + new_vn2 * ny;
        }
    }
}