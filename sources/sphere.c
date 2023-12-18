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
    printf("bear breadadadadada\n");

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
    // Convert float color values to integer values in the range [0, 255]
    int red = 255.999 * color_vec->x;
    int green = 255.999 * color_vec->y;
    int blue = 255.999 * color_vec->z;

    // Ensure the values are within the valid range [0, 255]
    red = (red < 0) ? 0 : (red > 255) ? 255 : red;
    green = (green < 0) ? 0 : (green > 255) ? 255 : green;
    blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;

    // Return the color as an integer
    return (red << 16) | (green << 8) | blue;
}


// Function to calculate the color of a ray intersection with the scene
struct s_vector3 *ray_color(struct s_ray *r, struct s_scene *scene) {
    (void)scene;
    float t = hit_sphere(&(struct s_vector3){0, 0, -1}, 0.5, r);
    if (t > 0.0) {
        struct s_vector3 *N = normalize(vector_subtract(ray_at(r, t), &(struct s_vector3){0, 0, -1}));
        return scalar_multiply(vector_add(N, &(struct s_vector3){1.0, 1.0, 1.0}), 0.5);
    }

    struct s_vector3 *unit_direction = normalize(r->direction);
    float a = 0.5 * (unit_direction->y + 1.0);
    
    // Replace the color function with vector operations
    struct s_vector3 *white = &(struct s_vector3){1.0, 1.0, 1.0};
    struct s_vector3 *blue = &(struct s_vector3){0.5, 0.7, 1.0};

    struct s_vector3 *term1 = scalar_multiply(white, 1.0 - a);
    struct s_vector3 *term2 = scalar_multiply(blue, a);

    return vector_add(term1, term2);
}

// Function to draw the scene
void draw_scene(struct s_scene *scene, struct s_data *img, void *mlx, void *win) {
    float aspect_ratio = 16.0 / 9.0;
    float image_width = img->width;

    // Calculate the image height, and ensure that it's at least 1.
    float image_height = image_width / aspect_ratio;
    image_height = (image_height < 1.0) ? 1.0 : image_height;

    // Camera parameters
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (image_width / image_height);
    struct s_vector3 *camera_center = &(struct s_vector3){0, 0, 0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    struct s_vector3 *viewport_u = &(struct s_vector3){viewport_width, 0, 0};
    struct s_vector3 *viewport_v = &(struct s_vector3){0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    struct s_vector3 *pixel_delta_u = scalar_multiply(viewport_u, 1 / image_width);
    struct s_vector3 *pixel_delta_v = scalar_multiply(viewport_v, 1 / image_height);

    // Calculate the location of the upper left pixel.
    struct s_vector3 *viewport_upper_left = vector_subtract(
        vector_subtract(
            vector_subtract(camera_center, &(struct s_vector3){0, 0, focal_length}),
            scalar_multiply(viewport_u, 1 / 2)),
        scalar_multiply(viewport_v, 1 / 2));

    struct s_vector3 *pixel00_loc = vector_add(
        viewport_upper_left,
        scalar_multiply(vector_add(pixel_delta_u, pixel_delta_v), 0.5));

    printf("bear breadadadadada\n");

    // Render
    for (int j = 0; j < image_height; ++j) {
        printf("j: %d\n", j);
        for (int i = 0; i < image_width; ++i) {
            struct s_vector3 *pixel_center = vector_add(
                pixel00_loc,
                vector_add(
                    scalar_multiply(pixel_delta_u, i),
                    scalar_multiply(pixel_delta_v, j)));

            struct s_vector3 *ray_direction = vector_subtract(pixel_center, camera_center);
            printf("seg fault a\n");

            struct s_ray *r = &(struct s_ray){camera_center, ray_direction};
            printf("seg fault b\n");


            // Use the ray_color function to get the color at the intersection point
            struct s_vector3 *pixel_color = ray_color(r, scene);
            printf("seg fault c\n");

            // Use the existing functions to write the color to the console and display it
            int color_int = write_color(pixel_color);
            (void)color_int;
            printf("seg fault d\n");
            plot_pixel(mlx, win, img, i, j, 0xFF000000);
            printf("j: %d, i: %d\n", j, i);

        }
    }
}

// Function to begin the drawing process
int begin_drawing(struct s_scene *myScene, struct s_data *data) {
    draw_scene(myScene, data, data->mlx_and_win->mlx, data->mlx_and_win->win);
    return 0;
}

