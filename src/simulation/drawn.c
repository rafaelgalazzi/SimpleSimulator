#include "drawn.h"

void setup2D(int *width, int *height)
{
    glViewport(0, 0, *width, *height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, *width, *height, 0.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawnPoint(Point *point)
{
    
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(point->diameter);
    glBegin(GL_POINTS);
    glColor3f(point->color[0], point->color[1], point->color[2]);
    glVertex2f(point->x, point->y);
    glEnd();
}

void drawnFrame(Point *point)
{
    drawnPoint(point);
}