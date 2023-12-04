#ifndef VEC3_DEVIANTS_H
#define VEC3_DEVIANTS_H

#include "../includes/minirt.h"

/* color start */


struct s_color *create_color(struct s_vec3 *this_vect)
{
    struct s_color *this_color = (struct s_color *)malloc(sizeof(struct s_color));
    this_color->e[0] = this_vect->e[0];
    this_color->e[1] = this_vect->e[1];
    this_color->e[2] = this_vect->e[2];

    return this_color;
}


//using the values of a colour struct, convert and return the values into a single integer value
int  write_color(struct s_vec3 *color_vec)
{
    int red = 255.999 * color_vec->e[0];
    int green = 255.999 * color_vec->e[1];
    int blue = 255.999 * color_vec->e[2];


    // Make sure the values are within the valid range (0-255)
    red = (red < 0) ? 0 : (red > 255) ? 255 : red;
    green = (green < 0) ? 0 : (green > 255) ? 255 : green;
    blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;

    // Convert to hexadecimal notation
    int color = 0xFF000000 | (red << 16) | (green << 8) | blue;

    // Print the result
    printf("Color in hexadecimal notation: 0x%08X\n", color);

    return color;
}

/* color end */


/* point3 start */


struct s_point3 *create_point3(struct s_vec3 *this_vect)
{
    struct s_point3 *this_point3 = (struct s_point3 *)malloc(sizeof(struct s_point3));
    this_point3->e[0] = this_vect->e[0];
    this_point3->e[1] = this_vect->e[1];
    this_point3->e[2] = this_vect->e[2];

    return this_point3;
}
/* point3 end */

/* ray start */

struct s_point3 *get_origin(struct s_ray *current_ray)
{
    return current_ray->ray_origin;
}

struct s_vec3 *get_direction(struct s_ray *current_ray)
{
    return current_ray->ray_direction;
}

struct s_point3 *get_ray_point_at_t(struct s_ray *current_ray, float t)
{
    struct s_point3 *result_point = (struct s_point3 *)malloc(sizeof(struct s_point3));
    result_point->e[0] = current_ray->ray_origin->e[0] + t*current_ray->ray_direction->e[0];
    result_point->e[1] = current_ray->ray_origin->e[1] + t*current_ray->ray_direction->e[1];
    result_point->e[2] = current_ray->ray_origin->e[2] + t*current_ray->ray_direction->e[2];
    return result_point;
}
/* ray end */

#endif