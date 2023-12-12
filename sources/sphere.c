#include "../includes/minirt.h"

float hit_sphere(struct s_vector3 *center, float radius, struct s_ray *r)
{
    struct s_vector3 *oc = vector_subtract(r->origin, center);
    float a = dot_product(r->direction, r->direction);
    float b = 2.0 * dot_product(oc, r->direction);
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;
    return ((-b - sqrtf(discriminant)) / (2.0 * a));
}

struct s_vector3 *get_ray_color(struct s_ray *r)
{
    float t = hit_sphere(&(struct s_vector3){0, 0, -1}, 0.5, r);
    if (t > 0.0)
    {
        struct s_vector3 *N = normalize(vector_subtract(ray_at(r, t), &(struct s_vector3){0, 0, -1}));
        return scalar_multiply(&(struct s_vector3){N->x + 1.0, N->y + 1.0, N->z + 1.0}, 0.5);
    }

    struct s_vector3 *unit_direction = normalize(r->direction);
    float a = 0.5 * (unit_direction->y + 1.0);
    return vector_add(scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 0.5), scalar_multiply(&(struct s_vector3){0.5, 0.7, 1.0}, a));
}


int  write_color(struct s_vector3 *color_vec)
{
    int red = 255.999 * color_vec->x;
    int green = 255.999 * color_vec->y;
    int blue = 255.999 * color_vec->z;


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


void draw_circle(void *mlx, void *win, struct s_data *img, int center_x, int center_y, int radius, struct s_ray *ray)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y)
    {
        float hit = hit_sphere(&(struct s_vector3){center_x + x, center_y + y, 0}, radius, ray);
        if (hit > 0.0)
        {
            struct s_vector3 *color = get_ray_color(ray);
            plot_pixel(mlx, win, img, center_x + x, center_y + y, write_color(color));
        }

        hit = hit_sphere(&(struct s_vector3){center_x - x, center_y + y, 0}, radius, ray);
        if (hit > 0.0)
        {
            struct s_vector3 *color = get_ray_color(ray);
            plot_pixel(mlx, win, img, center_x - x, center_y + y, write_color(color));
        }

        x++;

        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
    }
}