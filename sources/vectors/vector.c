#include "../../includes/minirt.h"

t_vector create_t_vec(float x, float y, float z)
{
    return (t_vector){x,y,z};
}


t_vector print_vec(t_vector vec)
{
    printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

void normalise_vector(t_vector *vector)
{
    float len = vector_length(*vector);
    if (!len)
    {
        *vector = create_t_vec(0,0,0);
    }
    else{

        *vector = vector_multi_k(*vector, 1/len);
    }
}

float vector_dot_product(t_vector v1, t_vector v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) +(v1.z * v2.z));
}

float point_distance(t_vector v1, t_vector v2)
{
    return (sqrtf(powf(v2.x - v1.x, 2.0) + powf(v2.y - v1.y, 2.0) + powf(v2.z - v1.z, 2.0)));
}