#ifndef RAY_H
#define RAY_H

typedef struct s_ray_init {
    float point_x;
    float point_y;
    float point_z;

    float direction_x;
    float direction_y;
    float direction_z;
}               t_ray_init;


void allocate_point_to_ray(t_ray_init *ray, float *point_array);

void allocate_direction_to_ray(t_ray_init *ray, float *dir_array);

float *find_point_on_ray(t_ray_init *ray, double t);

#endif