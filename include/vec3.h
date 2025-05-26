#ifndef __VEC3_H_
#define __VEC3_H_

#include <math.h>
#include <string.h>

typedef float vec3[3];

void matrix_set(float mat[4][4], float v);
void vec3_scale(float vector[3], float scale, float dest[3]);
void vec3_cross(float vec1[3], float vec2[3], float result[3]);
void vec3_normalize(float vec[3], float result[3]);
float vec3_dot(float vec1[3], float vec2[3]);
void matrix_rotate(float mat[4][4], float angle, float axis[3]);
void vec4_muladds(float inp[4], float s, float dest[4]);
void matrix_translate(float mat[4][4], float vec[3]);
void matrix_perspective(float fovy, float aspect, float near_z, float far_z, float mat[4][4]);
void look_at(float eye[3], float center[3], float up[3], float mat[4][4]);

#endif