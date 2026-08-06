#include "drawn.h"

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