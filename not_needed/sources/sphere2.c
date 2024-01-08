#include "../includes/minirt.h"

int hit_sphere2(struct s_vector3 *center, float radius, struct s_ray *r)
{
    struct s_vector3 *oc = vector_subtract(r->origin, center);
    double a = dot_product(r->direction, r->direction);
    double b = 2.0 * dot_product(oc, r->direction);
    double c = dot_product(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    // Check if the discriminant is non-negative to determine if there is an intersection
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        // Return the value of t at the intersection point
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }

}

struct s_vector3 *ray_color_sphere(struct s_ray *r)
{
    if (hit_sphere2(&(struct s_vector3){0, 0, -1}, 0.5, r))
    {
        return &(struct s_vector3){1, 0, 0};
    }

    struct s_vector3 *unit_direction = normalize(r->direction);
    float a = 0.5 * (unit_direction->y + 1.0);
    return vector_add(scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 1.0 - a), scalar_multiply(&(struct s_vector3){0.5, 0.7, 1.0}, a));
}

void draw_sphere(struct s_scene *scene, struct s_data *img, void *mlx, void *win)
{
    // Image
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * ((float)image_width / image_height);
    struct s_vector3 *camera_center = &(struct s_vector3){0.0, 0.0, 0.0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    struct s_vector3 *viewport_u = &(struct s_vector3){viewport_width, 0.0, 0.0};
    struct s_vector3 *viewport_v = &(struct s_vector3){0.0, -viewport_height, 0.0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    struct s_vector3 *pixel_delta_u = scalar_multiply(viewport_u, 1.0 / image_width);
    struct s_vector3 *pixel_delta_v = scalar_multiply(viewport_v, 1.0 / image_height);

    // Calculate the location of the upper left pixel.
    struct s_vector3 *viewport_upper_left = vector_subtract(
        vector_subtract(
            vector_subtract(camera_center, scalar_multiply(viewport_u, 0.5)),
            scalar_multiply(viewport_v, 0.5)
        ),
        scalar_multiply(&(struct s_vector3){0.0, 0.0, focal_length}, 1.0)
    );
    struct s_vector3 *pixel00_loc = vector_add(viewport_upper_left, scalar_multiply(vector_add(pixel_delta_u, pixel_delta_v), 0.5));

    // Render
    for (int j = 0; j < image_height; ++j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            struct s_vector3 *pixel_center = vector_add(pixel00_loc, vector_add(scalar_multiply(pixel_delta_u, (float)i), scalar_multiply(pixel_delta_v, (float)j)));
            struct s_vector3 *ray_direction = vector_subtract(pixel_center, camera_center);
            struct s_ray *ray = initializeCameraRay(scene->camera);
            ray->direction = normalize(ray_direction);

            // Check if the ray intersects with the sphere
            double t = hit_sphere2(scene->sphere->center, scene->sphere->diameter / 2.0, ray);
            if (t > 0)
            {
                // Get the color for the current pixel using the sphere color function
                struct s_vector3 *color = ray_color_sphere(ray);

                // Convert the color to an integer representation
                int int_color = write_color(color);

                // Plot the pixel on the screen
                plot_pixel(mlx, win, img, i, j, int_color);
            }
        }
    }
}



