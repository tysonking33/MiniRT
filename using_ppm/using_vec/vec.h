#ifndef VEC_H
#define VEC_H


#define WIDTH 800
#define HEIGHT 600

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Struct definition
typedef struct s_vec3 {
    float x, y, z;
} t_vec3;

// Constructors
struct s_vec3 *make_vec3(float x, float y, float z);

// Accessors
float get_vec3_x(struct s_vec3 *v);
float get_vec3_y(struct s_vec3 *v);
float get_vec3_z(struct s_vec3 *v);

// Unary operators
struct s_vec3 *vec3_neg(struct s_vec3 *v);

// Indexing
float vec3_at(struct s_vec3 *v, int i);

// Compound assignment operators
struct s_vec3 * vec3_mul_float(struct s_vec3 * v, float t);
struct s_vec3 *vec3_div(struct s_vec3 *v, float t);

// Length-related functions
float vec3_length(struct s_vec3 *v);
float vec3_length_squared(struct s_vec3 *v);

// Vector utility functions
void vec3_print(struct s_vec3 *v);
struct s_vec3 *vec3_add(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_sub(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 * vec3_mul_vec(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_scale(float t, struct s_vec3 *v);
float vec3_dot(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_cross(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_unit_vector(struct s_vec3 *v);

// Free memory for vec3
void free_vec3(struct s_vec3 *v);


/*in using_vect.c */
void write_color(FILE *file, struct s_vec3 * color);
int main();

#endif // VEC_H
