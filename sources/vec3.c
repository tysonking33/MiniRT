#include "../includes/minirt.h"

void set_x(struct s_vec3 *this_vect, float x)
{
    this_vect->e[0] = x;
}
void set_y(struct s_vec3 *this_vect, float y)
{
    this_vect->e[1] = y;
}

void set_z(struct s_vec3 *this_vect, float z)
{
    this_vect->e[2] = z;
}

void set_vec3(struct s_vec3 *this_vect, float *new_arr)
{
    this_vect->e[0] = new_arr[0];
    this_vect->e[1] = new_arr[1];
    this_vect->e[2] = new_arr[2];
}

struct s_vec3 *set_vec3_all(float x, float y, float z)
{
    struct s_vec3 *result_vec = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    result_vec->e[0] = x;
    result_vec->e[1] = y;
    result_vec->e[2] = z;

    return result_vec;
}

struct s_vec3 *vec_add_value(struct s_vec3 *this_vect, struct s_vec3 *vect2)
{
    this_vect->e[0] += vect2->e[0];
    this_vect->e[1] += vect2->e[1];
    this_vect->e[2] += vect2->e[2];
    return this_vect;
}

struct s_vec3 *vec_mutliply_value(struct s_vec3 *this_vect, float multiply_value)
{
    this_vect->e[0] *= multiply_value;
    this_vect->e[1] *= multiply_value;
    this_vect->e[2] *= multiply_value;
    return this_vect;
}

struct s_vec3 *vec_divide_value(struct s_vec3 *this_vect, float divide_value)
{
    if (divide_value != 0.0f) {
        return vec_mutliply_value(this_vect, 1.0f / divide_value);
    }
    return NULL;
}

float vec_length(struct s_vec3 *this_vect)
{
    return sqrt(length_squared(this_vect));
}

float length_squared(struct s_vec3 *this_vect)
{
    return powf(this_vect->e[0], 2) + powf(this_vect->e[1], 2) + powf(this_vect->e[2], 2);
}

void print_vec(struct s_vec3 *this_vect)
{
    printf("this_vect->e[0]: %f, this_vect->e[1]: %f, this_vect->e[2]: %f\n", this_vect->e[0], this_vect->e[1], this_vect->e[2]);
}

struct s_vec3 *vec_u_plus_v(struct s_vec3 *u, struct s_vec3 *v)
{
    return set_vec3_all(u->e[0] + v->e[0], u->e[1] + v->e[1], u->e[2] + v->e[2]);
}

struct s_vec3 *vec_u_minus_v(struct s_vec3 *u, struct s_vec3 *v)
{
    return set_vec3_all(u->e[0] - v->e[0], u->e[1] - v->e[1], u->e[2] - v->e[2]);
}

struct s_vec3 *vec_u_multiply_v(struct s_vec3 *u, struct s_vec3 *v)
{
    return set_vec3_all(u->e[0] * v->e[0], u->e[1] * v->e[1], u->e[2] * v->e[2]);
}

float dot_product(struct s_vec3 *u, struct s_vec3 *v)
{
    return u->e[0] * v->e[0] + u->e[1] * v->e[1] + u->e[2] * v->e[2];
}

struct s_vec3 *cross_product(struct s_vec3 *u, struct s_vec3 *v)
{
    return set_vec3_all(u->e[1] * v->e[2] - u->e[2] * v->e[1],
                u->e[2] * v->e[0] - u->e[0] * v->e[2],
                u->e[0] * v->e[1] - u->e[1] * v->e[0]);
}

struct s_vec3 *find_unit_vector(struct s_vec3 *u)
{
    return vec_divide_value(u, vec_length(u));
}