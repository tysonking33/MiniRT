#include "../../includes/minirt.h"

t_vector vector_add_vector(t_vector v1, t_vector v2)
{
    return create_t_vec((v1.x + v2.x),(v1.y + v2.y),(v1.z + v2.z));
}

t_vector vector_subtract_vector(t_vector v1, t_vector v2)
{
    return create_t_vec((v1.x - v2.x),(v1.y - v2.y),(v1.z - v2.z));
}

t_vector vector_multi_k(t_vector v1, float k)
{
    return create_t_vec((v1.x * k),(v1.y * k),(v1.z * k));
}

float vector_length(t_vector vect)
{
    return sqrt(vector_dot_product(vect, vect));
}