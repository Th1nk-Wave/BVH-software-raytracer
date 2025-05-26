#include "ray.h"

void intersect_triangle( ray* ray, const triangle* tri) {
    vec3 edge1;
    edge1[0] = tri->vertex1[0] - tri->vertex0[0];
    edge1[1] = tri->vertex1[1] - tri->vertex0[1];
    edge1[2] = tri->vertex1[2] - tri->vertex0[2];

    vec3 edge2;
    edge2[0] = tri->vertex2[0] - tri->vertex0[0];
    edge2[1] = tri->vertex2[1] - tri->vertex0[1];
    edge2[2] = tri->vertex2[2] - tri->vertex0[2];

    vec3 h;
    vec3_cross(ray->D, edge2, h);

    const float a = vec3_dot(edge1, h);

    if (a > -0.0001f && a < 0.0001f) return; // ray parallel to triangle

    const float f = 1/a;
    
    vec3 s;
    s[0] = ray->O[0] - tri->vertex0[0];
    s[1] = ray->O[1] - tri->vertex0[1];
    s[2] = ray->O[2] - tri->vertex0[2];

    const float u = f * vec3_dot(s,h);

    if (u < 0 || u > 1) return;

    vec3 q;
    vec3_cross(s, edge1, q);

    const float v = f * vec3_dot(ray->D, q);

    if (v < 0 || u + v > 1) return;

    const float t = f * vec3_dot(edge2, q);

    if (t > 0.0001f) ray->t = min(ray->t, t);

}