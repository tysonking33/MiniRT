#ifndef MATH_H
#define MATH_H

#include "./Data.h"
#include <math.h>
#include <stdint.h>

#define PI 3.14159265

struct s_vec3 vec3_sub(struct s_vec3 lhs, struct s_vec3 rhs);
struct s_vec3 vec3_add(struct s_vec3 lhs, struct s_vec3 rhs);
float dot(struct s_vec3  a, struct s_vec3  b);
struct s_vec3 vec3_normalize(struct s_vec3 v);
float intersectRaySphere(struct s_ray ray, struct s_sphere sphere);
struct s_vec3 computeNormalSphere(struct s_vec3 intersectionPoint, struct s_sphere sphere);
float vec3_magnitude(struct s_vec3 a);
struct s_vec3 scalarMult(struct s_vec3 v, float k);
struct s_vec3 rayAt(struct s_ray ray, float t);

struct s_vec3 scalarAdd(struct s_vec3 v, float k);
float maxft(float a, float b);
float minft(float a, float b);
struct s_vec3 createVec3(float x, float y, float z);



#endif