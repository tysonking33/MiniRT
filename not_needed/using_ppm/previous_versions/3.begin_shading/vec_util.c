#include "vec.h"

// Constructors
struct s_vec3 * make_vec3(float x, float y, float z) {
    struct s_vec3 * v = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

// Accessors
float get_vec3_x(struct s_vec3 *v) { return v->x; }
float get_vec3_y(struct s_vec3 *v) { return v->y; }
float get_vec3_z(struct s_vec3 *v) { return v->z; }

// Unary operators
struct s_vec3 *vec3_neg(struct s_vec3 *v) {
    return make_vec3(-v->x, -v->y, -v->z);
}

// Indexing
float vec3_at(struct s_vec3 *v, int i) {
    return (&v->x)[i];
}

// Compound assignment operators

struct s_vec3 * vec3_mul_float(struct s_vec3 * v, float t) {
    return make_vec3(v->x * t, v->y * t, v->z * t);
}

struct s_vec3 * vec3_div(struct s_vec3 * v, float t) {
    return vec3_mul_float(v, 1 / t);
}

// Length-related functions
float vec3_length(struct s_vec3 *v) {
    return sqrt(vec3_length_squared(v));
}

float vec3_length_squared(struct s_vec3 *v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

// Vector utility functions

void vec3_print(struct s_vec3 *v) {
    printf("%f %f %f\n", v->x, v->y, v->z);
}

struct s_vec3 * vec3_add(struct s_vec3 *u, struct s_vec3 *v) {
    return make_vec3(u->x + v->x, u->y + v->y, u->z + v->z);
}

struct s_vec3 * vec3_sub(struct s_vec3 *u, struct s_vec3 *v) {
    return make_vec3(u->x - v->x, u->y - v->y, u->z - v->z);
}

struct s_vec3 * vec3_mul_vec(struct s_vec3 *u, struct s_vec3 *v) {
    return make_vec3(u->x * v->x, u->y * v->y, u->z * v->z);
}

struct s_vec3 * vec3_scale(float t, struct s_vec3 *v) {
    return make_vec3(t * v->x, t * v->y, t * v->z);
}


float vec3_dot(struct s_vec3 *u, struct s_vec3 *v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

struct s_vec3 * vec3_cross(struct s_vec3 *u, struct s_vec3 *v) {
    return make_vec3(u->y * v->z - u->z * v->y,
                     u->z * v->x - u->x * v->z,
                     u->x * v->y - u->y * v->x);
}

struct s_vec3 * vec3_unit_vector(struct s_vec3 *v) {
    return vec3_div(v, vec3_length(v));
}

// Free memory for vec3
void free_vec3(struct s_vec3 * v) {
    //(void)v;
    free(v);
}
