#ifndef VEC3_DEVIANTS_H
#define VEC3_DEVIANTS_H

#include "../includes/minirt.h"

/* color start */

typedef struct s_color {
    float e[3];
} t_color;

// Function prototypes
struct s_color *create_color(struct s_vec3 *this_vect);
int write_color(struct s_vec3 *color_vec);

/* color end */


/* point3 start */

typedef struct s_point3 {
    float e[3];
} t_point3;

// Function prototypes
struct s_point3 *create_point3(struct s_vec3 *this_vect);

/* point3 end */

/* ray start */

typedef struct s_ray {
    struct s_point3 *ray_origin;
    struct s_vec3 *ray_direction;
} t_ray;

// Function prototypes
struct s_point3 *get_origin(struct s_ray *current_ray);
struct s_vec3 *get_direction(struct s_ray *current_ray);
struct s_point3 *get_ray_point_at_t(struct s_ray *current_ray, float t);

/* ray end */

#endif