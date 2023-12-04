#ifndef VEC3_H
#define VEC3_H

#include "../includes/minirt.h"

typedef struct s_vec3
{
    float e[3];

} t_vec3;

// Function prototypes
void set_x(struct s_vec3 *this_vect, float x);
void set_y(struct s_vec3 *this_vect, float y);
void set_z(struct s_vec3 *this_vect, float z);

void set_vec3(struct s_vec3 *this_vect, float *new_arr);
struct s_vec3 *set_vec3_all(float x, float y, float z);

struct s_vec3 *vec_add_value(struct s_vec3 *this_vect, struct s_vec3 *vect2);
struct s_vec3 *vec_mutliply_value(struct s_vec3 *this_vect, float multiply_value);
struct s_vec3 *vec_divide_value(struct s_vec3 *this_vect, float divide_value);

float vec_length(struct s_vec3 *this_vect);
float length_squared(struct s_vec3 *this_vect);

void print_vec(struct s_vec3 *this_vect);

struct s_vec3 *vec_u_plus_v(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec_u_minus_v(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec_u_multiply_v(struct s_vec3 *u, struct s_vec3 *v);

float dot_product(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *cross_product(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *find_unit_vector(struct s_vec3 *u);

#endif