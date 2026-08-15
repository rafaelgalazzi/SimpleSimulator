#ifndef ENTITY_H
#define ENTITY_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>

typedef struct Point
{
    float x;        // Position x in pixels
    float y;        // Position x in pixels
    float vx;       // Pixels per Second
    float vy;       // Pixels per Second
    float mass;     // Mass to apply physics
    float diameter; // Diameter in pixels
    float color[3];
} Point;

Point create_point(float x, float y, float vx, float vy, float mass, float diameter, float color[3]);

void create_many_points(Point *points, size_t point_amount);

#endif