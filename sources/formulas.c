#include "../includes/minirt.h"

float * vector_addition(float *vectora, float *vectorb)
{
    float *result_vector = (float *)malloc(3*sizeof(vectora));
    result_vector[0] = vectora[0] + vectorb[0];
    result_vector[1] = vectora[1] + vectorb[1];
    result_vector[2] = vectora[2] + vectorb[2];

    return result_vector;
}

float * vector_subtraction(float *vectora, float *vectorb)
{
    float *result_vector = (float *)malloc(3*sizeof(vectora));
    result_vector[0] = vectora[0] - vectorb[0];
    result_vector[1] = vectora[1] - vectorb[1];
    result_vector[2] = vectora[2] - vectorb[2];

    return result_vector;
}

float dot_product(float *vectora, float *vectorb)
{
    float result = vectora[0] * vectorb[0];
    result += vectora[1] * vectorb[1];
    result += vectora[2] * vectorb[2];

    return result;
}

float *vector_float_multiplication(float *vectora, float value)
{
    float *result_vector = (float *)malloc(3*sizeof(vectora));
    result_vector[0] = vectora[0] * value;
    result_vector[1] = vectora[1] * value;
    result_vector[2] = vectora[2] * value;

    return result_vector;
}

float vector_length(float *vectora)
{
    return sqrt(pow(vectora[0], 2) + pow(vectora[1], 2) + pow(vectora[2], 2));
}

float *cross_product(float *vectora, float *vectorb)
{
    float *result_vector = (float *)malloc(3*sizeof(vectora));
    result_vector[0] = vectora[1]*vectorb[2] - vectora[2]*vectorb[1];                 //x
    result_vector[1] = vectora[2]*vectorb[0] - vectora[0]*vectorb[2];                 //y
    result_vector[2] = vectora[0]*vectorb[1] - vectora[1]*vectorb[0];                 //z
    return result_vector;
}

float *find_ray_equation(float *vectora, float *direction_vector, float parameter_value)
{
    float *result_vector = (float *)malloc(3*sizeof(vectora));

    result_vector = vector_addition(vectora, vector_float_multiplication(direction_vector, parameter_value));

    return result_vector;
}


float *orthogonal_projection_single_vec(float *vectoru, float *vectorv, float *singular_subspace)
{
    float denominator = pow(vector_length(singular_subspace), 2);
    if (denominator == 0)
    {
        printf("ERROR: divide by zero\n");
        return NULL;
    }
    float lhs_value = dot_product(vectorv, singular_subspace)/ denominator;

    float *result = vector_float_multiplication(vectoru, lhs_value);
    if (result == NULL)
    {
        printf("ERROR: failed to vector_float_multiplication(vectoru, lhs_value)\n");
        return NULL;
    }
    return result;
}

float *convert_orthogonal_project_to_2d(float *vectoru, float *viewpoint_xyz)
{
    float viewport_width = 1920;
    float viewport_height = 1080;
    //perspective projection
    float x_2d = viewpoint_xyz[0] / viewpoint_xyz[2];
    float y_2d = viewpoint_xyz[1] / viewpoint_xyz[2];

    //map to viewport
    float x_screen  = (x_2d + 1) * (viewport_width / 2);
    float y_screen = (1 - y_2d) * (viewport_height / 2);

    float *result_vector = (float *)malloc(2*sizeof(vectoru));
    result_vector[0] = x_screen;
    result_vector[1] = y_screen;
    
    return result_vector;
}