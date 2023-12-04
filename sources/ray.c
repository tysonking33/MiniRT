/* for commands involving ray */
#include "../includes/minirt.h"
#include "../includes/ray.h"


void allocate_point_to_ray(t_ray_init *ray, float *point_array)
{
    ray->point = (float *)malloc(3 * sizeof(float));
    ray->point = point_array;
}

void allocate_direction_to_ray(t_ray_init *ray, float *dir_array)
{
    ray->direction = (float *)malloc(3 * sizeof(float));
    ray->direction = dir_array;
}

float *find_point_on_ray(t_ray_init *ray, double t)
{
    float *t_point_array = (float *)malloc(3 * sizeof(float));
    t_point_array[0] = ray->point->point_xyz_array[0] + t*ray->direction->point_xyz_array[0];
    t_point_array[1] = ray->point->point_xyz_array[1] + t*ray->direction->point_xyz_array[1];
    t_point_array[2] = ray->point->point_xyz_array[2] + t*ray->direction->point_xyz_array[2];
    return t_point_array;
}
