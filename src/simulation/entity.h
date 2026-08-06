#ifndef ENTITY_H
#define ENTITY_H
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

#endif