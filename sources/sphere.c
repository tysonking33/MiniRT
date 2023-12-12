#include "../includes/minirt.h"

// return true = 1 or false = 2
int hit_sphere(struct s_point3 *center, float radius, struct s_ray *r)
{
    struct s_vec3 *oc = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    oc->e[0] = r->ray_origin->e[0] - center->e[0];
    oc->e[1] = r->ray_origin->e[1] - center->e[1];
    oc->e[2] = r->ray_origin->e[2] - center->e[2];


    float a = dot_product(r->ray_direction, r->ray_direction);
    float b = 2.0 * dot_product(oc, r->ray_direction);
    float c = dot_product(oc,oc) - radius* radius;
    float discriminant = b *b - 2*a*c;
    free(oc);

    if (discriminant >= 0)
        return 1;
    return 0;

}

struct s_color *get_ray_color(struct s_ray *r)
{
    struct s_point3 *current_point3 = (struct s_point3 *)malloc(sizeof(struct s_point3));
    current_point3->e[0] = 0;
    current_point3->e[1] = 0;
    current_point3->e[2] = -1;
    if (hit_sphere(current_point3, 0.5, r) == 1)
    {
        struct s_color *return_color = (struct s_color *)malloc(sizeof(struct s_color));
        return_color->e[0] = 1;
        return_color->e[1] = 0;
        return_color->e[2] = 0;

        return return_color;
    }

    struct s_vec3 *unit_direction = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    unit_direction = find_unit_vector(r->ray_direction);
    float a = 0.5 * (unit_direction->e[1] + 1.0);

    struct s_color *return_color = (struct s_color *)malloc(sizeof(struct s_color));
    return_color->e[0] = (1.0-a)*1.0 + a*0.5;
    return_color->e[1] = (1.0-a)*1.0 + a*0.7;
    return_color->e[2] = (1.0-a)*1.0 + a*1.0;
    free(unit_direction);
    return return_color;

}

void plot_sphere(void *mlx, void *mlx_win, struct s_data *img, struct s_point3 *center, float radius, struct s_ray *camera)
{
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            // Calculate ray direction for the current pixel
            struct s_ray pixel_ray;

            // Set the ray origin to the camera position
            pixel_ray.ray_origin = camera->ray_origin;

            // Set the ray direction to the vector from the camera to the current pixel
            pixel_ray.ray_direction = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
            pixel_ray.ray_direction->e[0] = x - camera->ray_origin->e[0];
            pixel_ray.ray_direction->e[1] = y - camera->ray_origin->e[1];
            pixel_ray.ray_direction->e[2] = -1.0 * camera->ray_origin->e[2];  // Adjust as needed

            // Check if the pixel belongs to the sphere
            if (hit_sphere(center, radius, &pixel_ray) == 1)
            {
                // If yes, set the pixel color to red
                plot_pixel(mlx, mlx_win, img, x, y, 0xFF0000);
            }
            else
            {
                // If not, set the pixel color based on the ray direction
                struct s_color *color = get_ray_color(&pixel_ray);
                int pixel_color = (int)(color->e[0] * 255) << 16 | (int)(color->e[1] * 255) << 8 | (int)(color->e[2] * 255);
                plot_pixel(mlx, mlx_win, img, x, y, pixel_color);
                free(color);
            }

            // Free memory for ray_direction
            free(pixel_ray.ray_direction);
        }
    }
}

