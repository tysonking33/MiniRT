#include "minirt.h"

// Function to compute the cross product of two vectors
struct s_vec3 *crossProduct(struct s_vec3 *a, struct s_vec3 *b) {
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = a->y * b->z - a->z * b->y;
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
    return result;
}

// Function to normalize a vector
struct s_vec3 *normalize(struct s_vec3 *v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = v->x / length;
    result->y = v->y / length;
    result->z = v->z / length;
    return result;
}

// Function to subtract two vectors
struct s_vec3 *subtract(struct s_vec3 *a, struct s_vec3 *b) {
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

// Function to add a scalar value to each component of a vector
struct s_vec3 *addScalar(struct s_vec3 *v, float scalar) {
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = v->x + scalar;
    result->y = v->y + scalar;
    result->z = v->z + scalar;
    return result;
}

// Function to multiply each component of a vector by a scalar value
struct s_vec3 *multiplyScalar(struct s_vec3 *v, float scalar) {
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = v->x * scalar;
    result->y = v->y * scalar;
    result->z = v->z * scalar;
    return result;
}

// Function to compute the dot product of two vectors
float dotProduct(struct s_vec3 *a, struct s_vec3 *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


struct s_vec3 *add(struct s_vec3 *a, struct s_vec3 *b) {
    struct s_vec3 *result = (struct s_vec3*)malloc(sizeof(struct s_vec3));
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
    return result;
}


float distance(struct s_vec3 *a, struct s_vec3 *b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;

    // Using the Euclidean distance formula
    return sqrt(dx * dx + dy * dy + dz * dz);
}