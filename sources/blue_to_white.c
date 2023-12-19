#include "../includes/minirt.h"

struct s_vector3 *ray_color_btw(struct s_ray *r)
{
    struct s_vector3 *unit_vector = normalize(r->direction);
    float t = 0.5 * (unit_vector->y + 1.0);
    return vector_add(scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 1.0 - t),
                     scalar_multiply(&(struct s_vector3){0.5, 0.7, 1.0}, t));
}

void draw_blue_to_white(struct s_scene *scene, struct s_data *img, void *mlx, void *win)
{
    for (int j = img->height - 1; j >= 0; --j)
    {
        for (int i = 0; i < img->width; ++i)
        {
            // Compute the ray direction for each pixel
            float u = (float)i / img->width;
            float v = (float)j / img->height;
            struct s_ray *ray = initializeCameraRay(scene->camera);

            // Update ray direction based on pixel coordinates
            ray->direction = vector_add(ray->direction, scalar_multiply(vector_subtract(&(struct s_vector3){u, v, 0.0}, ray->origin), 1.0));

            // Get the color for the current pixel using the blue-to-white gradient
            struct s_vector3 *color = ray_color_btw(ray);

            // Convert the color to an integer representation
            int int_color = write_color(color);

            // Plot the pixel on the screen
            plot_pixel(mlx, win, img, i, j, int_color);

            /*// Clean up the allocated memory for the ray and color
            free(ray->direction);
            free(ray->origin);
            free(ray);
            free(color);*/
        }
    }
}
