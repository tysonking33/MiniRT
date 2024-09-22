#ifndef MATH_H
#define MATH_H

#include "./Data.h"
#include <math.h>
#include <stdint.h>

#define PI 3.14159265

t_vec3 vec3_sub(t_vec3 lhs, t_vec3 rhs);
t_vec3 vec3_add(t_vec3 lhs, t_vec3 rhs);
float dot(t_vec3  a, t_vec3  b);
t_vec3 vec3_normalize(t_vec3 v);
float intersectRaySphere(t_ray ray, t_sphere sphere);
t_vec3 computeNormalSphere(t_vec3 intersectionPoint, t_sphere sphere);
float vec3_magnitude(t_vec3 a);
t_vec3 scalarMult(t_vec3 v, float k);
t_vec3 rayAt(t_ray ray, float t);

t_vec3 scalarAdd(t_vec3 v, float k);
float maxft(float a, float b);
float minft(float a, float b);
t_vec3 createVec3(float x, float y, float z);
float find_smaller_positive_float(float a, float b);

void printVec3(char *string, t_vec3 vector);


#endif