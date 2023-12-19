#include "../includes/minirt.h"

// Function to add two vectors
struct s_vector3 *vector_add(struct s_vector3 *A, struct s_vector3 *B)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));

    if (result != NULL)
    {
        // Perform the vector addition
        result->x = A->x + B->x;
        result->y = A->y + B->y;
        result->z = A->z + B->z;
    }

    return result;
}

// Function to subtract one vector from another
struct s_vector3 *vector_subtract(struct s_vector3 *A, struct s_vector3 *B)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));

    if (result != NULL)
    {
        // Perform the vector subtraction
        result->x = (A->x - B->x);
        result->y = (A->y - B->y);
        result->z = (A->z - B->z);
    }

    return result;
}


// Function to perform scalar multiplication on a vector
struct s_vector3 *scalar_multiply(struct s_vector3 *A, float k)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));

    if (result != NULL)
    {
        // Perform the vector multiplication
        result->x = A->x * k;
        result->y = A->y * k;
        result->z = A->z * k;
    }

    return result;
}

// Function to calculate the dot product of two vectors
float dot_product(struct s_vector3 *A, struct s_vector3 *B)
{
    return (A->x * B->x) + (A->y * B->y) + (A->z * B->z);
}

// Function to calculate the cross product of two vectors
struct s_vector3 *cross_product(struct s_vector3 *A, struct s_vector3 *B)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));

    if (result != NULL)
    {
        // Perform the vector multiplication
        result->x = A->y * B->z - A->z * B->y;
        result->y = A->z * B->x - A->x * B->z;
        result->z = A->x * B->y - A->y * B->x;
    }

    return result;
}

// Function to normalize a vector (convert to a unit vector)
struct s_vector3 *normalize(struct s_vector3 *A)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));
    float a_magnitude = vector_magnitude(A);
    if (result != NULL && a_magnitude != 0.0)
    {
        // Perform the vector multiplication
        result = scalar_multiply(A, 1 / a_magnitude);
    }

    return result;
}

// Function to calculate the projection of vector A onto vector B
struct s_vector3 *vector_projection(struct s_vector3 *A, struct s_vector3 *B)
{
    // Allocate memory for the result
    struct s_vector3 *result = malloc(sizeof(struct s_vector3));

    float a_dot_b = dot_product(A, B);
    float b_magnitude = vector_magnitude(B);

    if (result != NULL && b_magnitude != 0.0)
    {
        // Perform the vector multiplication
        result = scalar_multiply(B, (a_dot_b / b_magnitude));
    }

    return result;
}

// Function to calculate the angle (in radians) between two vectors
float angle_between_vectors(struct s_vector3 *A, struct s_vector3 *B)
{
    float a_dot_b = dot_product(A, B);
    float a_magnitude = vector_magnitude(A);
    float b_magnitude = vector_magnitude(B);

    // Ensure denominators are not zero
    if (a_magnitude == 0.0 || b_magnitude == 0.0)
    {
        printf("Cannot calculate angle. One or both vectors have zero magnitude.\n");
        return 0.0; // Return 0.0 as a default value
    }

    float theta = acosf(a_dot_b / (a_magnitude * b_magnitude));

    return theta;
}

// Function to calculate the magnitude (length) of a vector
float vector_magnitude(struct s_vector3 *A)
{
    return sqrtf(pow((A->x), 2) + pow((A->y), 2) + pow((A->z), 2));
}

// Function to calculate the distance between two points in 3D space
float distance_between_points(struct s_vector3 *P, struct s_vector3 *Q)
{
    return sqrtf(powf(P->x - Q->x, 2) + powf(P->y - Q->y, 2) + powf(P->z - Q->z, 2));
}

// Function to rotate a 2D vector counterclockwise by an angle theta
struct s_vector2 *rotate_2D_vector(struct s_vector2 *V, float theta)
{
    // Allocate memory for the result
    struct s_vector2 *result = malloc(sizeof(struct s_vector2));

    if (result != NULL)
    {
        // Perform the vector multiplication
        result->x = V->x * cosf(theta) - V->y * sinf(theta);
        result->y = V->x * sinf(theta) + V->y * cosf(theta);
    }

    return result;
}

struct s_vector3 *ray_at(struct s_ray *ray, float t)
{
    return vector_add(ray->origin, scalar_multiply(ray->direction, t));
}