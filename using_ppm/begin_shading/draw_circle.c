#include "vec.h"

// Function to check if a ray hits a sphere
float hit_sphere(struct s_vec3 *center, float radius, struct s_ray *r) {
    struct s_vec3 *oc = vec3_sub(get_origin(r), center);
    float a = vec3_dot(get_direction(r), get_direction(r));
    float b = 2.0 * vec3_dot(oc, get_direction(r));
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;
    return (-b - sqrtf(discriminant)) / (2.0 * a);
}

// Function to calculate color for a given ray
struct s_vec3 *ray_color(struct s_ray *r) {
    float t = hit_sphere(make_vec3(0, 0, -1), 0.5, r);
    float max_t = 800.0;  // Adjust this value based on your scene size

    if (t > 0.0 && t < max_t) {
        //printf("Intersection at t = %f\n", t);
        struct s_vec3 *N = vec3_unit_vector(vec3_sub(at(r, t), make_vec3(0, 0, -1)));
        //printf("Normal vector N: ");
        //vec3_print(N);

        struct s_vec3 *result = vec3_mul_float(vec3_add(N, make_vec3(1, 1, 1)), 0.5);
        free_vec3(N);
        //printf("Color at intersection: ");
        //vec3_print(result);
        return result;
    }

    struct s_vec3 *unit_direction = vec3_unit_vector(get_direction(r));
    float a = 0.5 * (get_vec3_y(unit_direction) + 1.0);

    struct s_vec3 *white = make_vec3(1.0, 1.0, 1.0);
    struct s_vec3 *blue = make_vec3(0.5, 0.7, 1.0);

    struct s_vec3 *result = vec3_add(vec3_mul_float(vec3_sub(white, blue), 1.0 - a), vec3_mul_float(blue, a));

    free_vec3(unit_direction);
    free_vec3(white);
    free_vec3(blue);

    return result;
}

void draw_circle() {
    // Image
    int image_width = WIDTH;
    int image_height = HEIGHT;

    // Camera
    struct s_vec3 *camera_center = make_vec3(0, 0, 0);

    // Render
    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        printf("\rScanlines remaining: %d ", (image_height - j));
        for (int i = 0; i < image_width; ++i) {
            // Map pixel coordinates to the range [-1, 1]
            float u = (2.0 * i) / (image_width - 1) - 1.0;
            float v = 1.0 - (2.0 * j) / (image_height - 1);

            // Create a ray for each pixel
            struct s_vec3 *origin = make_vec3(0, 0, 0);
            struct s_vec3 *direction = make_vec3(u, v, -1.0);  // Adjust the view direction as needed
            struct s_ray *ray = make_s_ray(origin, direction);

            // Calculate color using ray_color
            struct s_vec3 *pixel_color = ray_color(ray);

            // Write color to the image file
            write_color(image, pixel_color);

            // Free memory
            free_vec3(origin);
            free_vec3(direction);
            free_s_ray(ray);
            free_vec3(pixel_color);
        }
    }

    printf("\rDone.                 \n");

    fclose(image);

    // Cleanup
    free_vec3(camera_center);
}
