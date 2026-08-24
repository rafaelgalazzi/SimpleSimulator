#ifndef PHYSICS_H
#define PHYSICS_H

#include "../entity/entity.h"

void applyPhysics(Point *points, size_t point_amount, double *last_update_time);
void updatePosition(Point *point, double *delta_time);
void applyBoundaries(Point *point);
void apply_colision(Point *point1, Point *points, size_t point_amount, size_t current_index);

#endif