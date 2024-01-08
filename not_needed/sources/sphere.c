#include "../includes/minirt.h"

// Function to check if a ray intersects with a sphere
float hit_sphere(struct s_vector3 *center, float radius, struct s_ray *r)
{
    // Calculate vector from the ray's origin to the sphere's center
    struct s_vector3 *oc = vector_subtract(r->origin, center);

    // Coefficients for the quadratic equation
    float a = dot_product(r->direction, r->direction);
    float half_b = dot_product(oc, r->direction);
    float c = pow(vector_magnitude(oc), 2) - radius * radius;

    // Calculate the discriminant to determine if there is an intersection
    float discriminant = half_b * half_b - a * c;
    //printf("bear breadadadadada\n");

    // If the discriminant is negative, there is no intersection
    if (discriminant < 0)
        return -1.0;

    // Otherwise, return the closest intersection point
    return ((-half_b - sqrtf(discriminant)) / (a));
}

// Function to get the color of a ray's intersection point with a sphere
struct s_vector3 *get_ray_color(struct s_ray *r)
{
    // Check if the ray intersects with a sphere
    float t = hit_sphere(&(struct s_vector3){0, 0, -1}, 0.5, r);

    // If there is an intersection, calculate the color based on the surface normal
    if (t > 0.0)
    {
        struct s_vector3 *N = normalize(vector_subtract(ray_at(r, t), &(struct s_vector3){0, 0, -1}));
        return scalar_multiply(&(struct s_vector3){N->x + 1.0, N->y + 1.0, N->z + 1.0}, 0.5);
    }

    // If no intersection, calculate a background color based on the ray's direction
    struct s_vector3 *unit_direction = normalize(r->direction);
    float a = 0.5 * (unit_direction->y + 1.0);

    return vector_add(scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 0.5), scalar_multiply(&(struct s_vector3){0.5, 0.7, 1.0}, a));
}

// Function to write the color to the console and return the color as an integer
int write_color(struct s_vector3 *color_vec)
{
    // Scale and clamp each color component
    int red = (int)(255.999 * fmin(fmax(color_vec->x, 0.0), 1.0));
    int green = (int)(255.999 * fmin(fmax(color_vec->y, 0.0), 1.0));
    int blue = (int)(255.999 * fmin(fmax(color_vec->z, 0.0), 1.0));

    // Return the color as an integer
    return (red << 16) | (green << 8) | blue;
}

// Function to calculate the color of a ray's intersection point with a sphere
struct s_vector3 *ray_color(struct s_ray *r)
{
    // Check if the ray intersects with a sphere
    float t = hit_sphere(&(struct s_vector3){0, 0, -1}, 0.5, r);

    // If there is an intersection, return the color of the sphere
    if (t > 0.0)
    {
        // Calculate the intersection point on the sphere
        struct s_vector3 *intersection_point = ray_at(r, t);

        // Calculate the normal at the intersection point
        struct s_vector3 *N = normalize(vector_subtract(intersection_point, &(struct s_vector3){0, 0, -1}));

        // Calculate the Lambertian reflection (simple diffuse shading)
        float intensity = fmin(dot_product(N, &(struct s_vector3){1.0, 1.0, 1.0}), 1.0);

        // Create a pixel color based on the Lambertian reflection
        struct s_vector3 *pixel_color = scalar_multiply(&(struct s_vector3){intensity + 1.0, intensity + 1.0, intensity + 1.0}, 0.5);

        // Free the memory allocated for the intersection point and normal
        free(intersection_point);
        free(N);

        // Return the color of the sphere
        return pixel_color;
    }

    // If no intersection, return the background color
    return scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 0.5);
}


// Update the draw_scene function to fix memory issues
void draw_scene(struct s_scene *scene, struct s_data *img, void *mlx, void *win)
{
    (void)scene;
    float aspect_ratio = 16.0 / 9.0;
    float image_width = img->width;
    float image_height = image_width / aspect_ratio;
    image_height = (image_height < 1.0) ? 1.0 : image_height;

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (image_width / image_height);
    struct s_vector3 *camera_center = &(struct s_vector3){0, 0, 0};

    struct s_vector3 *viewport_u = &(struct s_vector3){viewport_width, 0, 0};
    struct s_vector3 *viewport_v = &(struct s_vector3){0, -viewport_height, 0};

    struct s_vector3 *pixel_delta_u = scalar_multiply(viewport_u, 1 / image_width);
    struct s_vector3 *pixel_delta_v = scalar_multiply(viewport_v, 1 / image_height);

    struct s_vector3 *viewport_upper_left = vector_subtract(
        vector_subtract(
            vector_subtract(camera_center, &(struct s_vector3){0, 0, focal_length}),
            scalar_multiply(viewport_u, 0.5)),
        scalar_multiply(viewport_v, 0.5));

    for (int j = 0; j < image_height; ++j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            struct s_vector3 *pixel_center = vector_add(
                viewport_upper_left,
                vector_add(scalar_multiply(pixel_delta_u, i), scalar_multiply(pixel_delta_v, j)));

            struct s_vector3 *ray_direction = normalize(vector_subtract(pixel_center, camera_center));
            struct s_ray *r = &(struct s_ray){camera_center, ray_direction};

            struct s_vector3 *pixel_color = ray_color(r);

            int color_int = write_color(pixel_color);

            plot_pixel(mlx, win, img, i, j, color_int);

            // Free the memory allocated for vectors and color
            free(pixel_center);
            free(ray_direction);
            free(pixel_color);
        }
    }
}

// Function to begin the drawing process
int begin_drawing(struct s_scene *myScene, struct s_data *data)
{
    draw_scene(myScene, data, data->mlx_and_win->mlx, data->mlx_and_win->win);
    return 0;
}
