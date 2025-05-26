#include "vec3.h"

void matrix_set(float mat[4][4], float v) {
	mat[0][0] = v; mat[0][1] = mat[0][2] = mat[0][3] = 0.f;
	mat[1][1] = v; mat[1][0] = mat[1][2] = mat[1][3] = 0.f;
	mat[2][2] = v; mat[2][0] = mat[2][1] = mat[2][3] = 0.f;
	mat[3][3] = v; mat[3][0] = mat[3][1] = mat[3][2] = 0.f;
}

void vec3_scale(float vector[3], float scale, float dest[3]) {
	dest[0] = vector[0] * scale;
	dest[1] = vector[1] * scale;
	dest[2] = vector[2] * scale;
}

void vec3_cross(float vec1[3], float vec2[3], float result[3]) {
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

float vec3_dot(float vec1[3], float vec2[3]) {
	return vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2];
}

void vec3_normalize(float vec[3], float result[3]) {
	vec3_scale(
		(vec),
		1.f / sqrtf(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]),
		result
	);
}

void matrix_rotate(float mat[4][4], float angle, float axis[3]) {
	float rot[4][4];
	memset(rot, 0.f, sizeof(rot));
	float c = cosf(angle);

	float norm_axis[3];
	vec3_scale(
		axis,
		1.f / sqrtf(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]),
		norm_axis
	);
	
	float vec[3], vecs[3];
	vec3_scale(norm_axis, 1.f-c, vec);
	vec3_scale(norm_axis, sinf(angle), vecs);

	vec3_scale(norm_axis, vec[0], rot[0]);
	vec3_scale(norm_axis, vec[1], rot[1]);
	vec3_scale(norm_axis, vec[2], rot[2]);

	rot[0][0] += c;       rot[1][0] -= vecs[2]; rot[2][0] += vecs[1];
	rot[0][1] += vecs[2]; rot[1][1] += c;       rot[2][1] -= vecs[0];
	rot[0][2] -= vecs[1]; rot[1][2] += vecs[0]; rot[2][2] += c;
	rot[0][3] = rot[1][3] = rot[2][3] = rot[3][0] = rot[3][1] = rot[3][2] = 0.f;
	rot[3][3] = 1.f;

	float a00 = mat[0][0], a01 = mat[0][1], a02 = mat[0][2], a03 = mat[0][3],
	      a10 = mat[1][0], a11 = mat[1][1], a12 = mat[1][2], a13 = mat[1][3],
	      a20 = mat[2][0], a21 = mat[2][1], a22 = mat[2][2], a23 = mat[2][3],
	      a30 = mat[3][0], a31 = mat[3][1], a32 = mat[3][2], a33 = mat[3][3],
	      b00 = rot[0][0], b01 = rot[0][1], b02 = rot[0][2],
	      b10 = rot[1][0], b11 = rot[1][1], b12 = rot[1][2],
	      b20 = rot[2][0], b21 = rot[2][1], b22 = rot[2][2];

	mat[0][0] = a00*b00 + a10*b01 + a20*b02;
	mat[0][1] = a01*b00 + a11*b01 + a21*b02;
	mat[0][2] = a02*b00 + a12*b01 + a22*b02;
	mat[0][3] = a03*b00 + a13*b01 + a23*b02;
	mat[1][0] = a00*b10 + a10*b11 + a20*b12;
	mat[1][1] = a01*b10 + a11*b11 + a21*b12;
	mat[1][2] = a02*b10 + a12*b11 + a22*b12;
	mat[1][3] = a03*b10 + a13*b11 + a23*b12;
	mat[2][0] = a00*b20 + a10*b21 + a20*b22;
	mat[2][1] = a01*b20 + a11*b21 + a21*b22;
	mat[2][2] = a02*b20 + a12*b21 + a22*b22;
	mat[2][3] = a03*b20 + a13*b21 + a23*b22; 
	mat[3][0] = a30; mat[3][1] = a31; mat[3][2] = a32; mat[3][3] = a33;
}

void vec4_muladds(float inp[4], float s, float dest[4]) {
	dest[0] += inp[0] * s;
	dest[1] += inp[1] * s;
	dest[2] += inp[2] * s;
	dest[3] += inp[3] * s;
}

void matrix_translate(float mat[4][4], float vec[3]) {
	vec4_muladds(mat[0], vec[0], mat[3]);
	vec4_muladds(mat[1], vec[1], mat[3]);
	vec4_muladds(mat[2], vec[2], mat[3]);
}

void matrix_perspective(float fovy, float aspect, float near_z, float far_z, float mat[4][4]) {
	matrix_set(mat, 0.f);
	float f = 1.f / tanf(fovy * .5f), fn = 1.f / (near_z - far_z);

	mat[0][0] = f / aspect;
	mat[1][1] = f;
	mat[2][2] = (near_z + far_z) * fn;
	mat[2][3] = -1.f;
	mat[3][2] = 2.f * near_z * far_z * fn;
}

void look_at(float eye[3], float center[3], float up[3], float mat[4][4]) {
	float f[3];
	float _[3];
	_[0] = center[0] - eye[0];
	_[1] = center[1] - eye[1];
	_[2] = center[2] - eye[2];
	vec3_normalize(_,f);

	float u[3];
	_[0] = up[0];
	_[1] = up[1];
	_[2] = up[2];
	vec3_normalize(_,u);

	float s[3];
	vec3_cross(f,u,_);
	vec3_normalize(_,s);

	vec3_cross(s,f,u);

	mat[0][0] = s[0];
	mat[1][0] = s[1];
	mat[2][0] = s[2];
	mat[0][1] = u[0];
	mat[1][1] = u[1];
	mat[2][1] = u[2];
	mat[0][2] =-f[0];
	mat[1][2] =-f[1];
	mat[2][2] =-f[2];
	mat[3][0] =-vec3_dot(s,eye);
	mat[3][1] =-vec3_dot(u,eye);
	mat[3][2] = vec3_dot(f,eye);
}