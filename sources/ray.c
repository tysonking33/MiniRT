/* for commands involving ray */
#include "../includes/minirt.h"
#include "../includes/ray.h"


void allocate_point_to_ray(t_ray_init *ray, float *point_array)
{
    ray->point_x = point_array[0];
    ray->point_y = point_array[1];
    ray->point_z = point_array[2];
}

void allocate_direction_to_ray(t_ray_init *ray, float *dir_array)
{
    ray->direction_x = dir_array[0];
    ray->direction_y = dir_array[1];
    ray->direction_z = dir_array[2];
}

float *find_point_on_ray(t_ray_init *ray, double t)
{
    float *t_point_array = (float *)malloc(3 * sizeof(float));
    t_point_array[0] = ray->point_x + t*ray->direction_x;
    t_point_array[1] = ray->point_y + t*ray->direction_y;
    t_point_array[2] = ray->point_z + t*ray->direction_z;
    return t_point_array;
}