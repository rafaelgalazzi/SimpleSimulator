#ifndef PHYSICS_H
#define PHYSICS_H

#include "../entity/entity.h"

void applyPhysics(Point *points, size_t point_amount);
void updatePosition(Point *point);
void applyBoundaries(Point *point);

#endif