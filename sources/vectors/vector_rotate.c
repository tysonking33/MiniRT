#include "../../includes/minirt.h"

//clockwise = 1, counterclockwise = 0
//zyx, xyz
t_vector ft_vector_rotate(t_vector vector, int clockwise)
{
    float tmp;
    if (clockwise)
    {
        tmp = vector.z;
        vector.z = vector.y;
        vector.y = vector.x;
        vector.x = tmp;
    }
    else{
        tmp = vector.x;
        vector.x = vector.y;
        vector.y = vector.z;
        vector.z = tmp;
    }

    return vector;
}