#include "raytracing.h"

// Function to add two vectors
struct s_vector *add_vectors(struct s_vector *v1, struct s_vector *v2)
{
    return make_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

// Function to subtract two vectors
struct s_vector *subtract_vectors(struct s_vector *v1, struct s_vector *v2)
{
    return make_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

// Function to multiply a vector by a scalar
struct s_vector *multiply_vector_scalar(struct s_vector *v, float scalar)
{
    return make_vector(v->x * scalar, v->y * scalar, v->z * scalar);
}

// Function to calculate the dot product of two vectors
float dot_product(struct s_vector *v1, struct s_vector *v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

// Function to calculate the cross product of two vectors
struct s_vector *cross_product(struct s_vector *v1, struct s_vector *v2)
{
    return make_vector(v1->y * v2->z - v1->z * v2->y,
                       v1->z * v2->x - v1->x * v2->z,
                       v1->x * v2->y - v1->y * v2->x);
}

// Function to normalize a vector
struct s_vector *normalize_vector(struct s_vector *v)
{
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    if (length == 0)
        return NULL;

    return make_vector(v->x / length, v->y / length, v->z / length);
}

// Function to reflect a vector around a normal
struct s_vector *reflect_vector(struct s_vector *incident, struct s_vector *normal)
{
    struct s_vector *normalized_normal = normalize_vector(normal);
    struct s_vector *scaled_normal = multiply_vector_scalar(normalized_normal, 2 * dot_product(incident, normalized_normal));
    return subtract_vectors(incident, scaled_normal);
}

// Function to add a scalar to each element of a vector
struct s_vector *add_scalar(struct s_vector *v, float t)
{
    return make_vector(v->x + t, v->y + t, v->z + t);
}

// Function to subtract a scalar from each element of a vector
struct s_vector *subtract_scalar(struct s_vector *v, float t)
{
    return make_vector(v->x - t, v->y - t, v->z - t);
}

// Function to divide each element of a vector by a scalar
struct s_vector *divide_scalar(struct s_vector *v, float t)
{
    // Check for division by zero to avoid potential issues
    if (t == 0.0f)
        return NULL;
    return multiply_vector_scalar(v, 1/t);
}

// Function to free memory allocated for a vector
void free_vector(struct s_vector *v)
{
    //free(v);
}
