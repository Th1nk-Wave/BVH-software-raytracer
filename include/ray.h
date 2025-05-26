#ifndef __RAY_H_
#define __RAY_H_

#include "defines.h"
#include "vec3.h"
#include "triangle.h"

typedef struct {
    vec3 O, D;
    float t;
} ray;

void intersect_triangle( ray* ray, const triangle* tri);


#endif