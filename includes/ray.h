#ifndef RAY_H
#define RAY_H

typedef struct s_point_init {
    float *point_xyz_array;

}               t_point_init;

typedef struct s_ray_init {
    struct s_plane_init *point;

    struct s_plane_init *direction;

}               t_ray_init;




void allocate_point_to_ray(t_ray_init *ray, float *point_array);

void allocate_direction_to_ray(t_ray_init *ray, float *dir_array);

float *find_point_on_ray(t_ray_init *ray, double t);

#endif