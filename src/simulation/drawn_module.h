#ifndef DRAWN_MODULE
#define DRAWN_MODULE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

typedef struct
{
    float x;
    float y;
    float vx;
    float xy;
    float mass;
    float diameter;
    float color[3];
} Point;

void drawnPoint(Point *point);

void drawnFrame();

#endif