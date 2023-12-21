#include "vec.h"

// Function to check if a ray hits a sphere
int hit_sphere(struct s_vec3 *center, float radius, struct s_ray *r) {
    struct s_vec3 *oc = vec3_sub(get_origin(r), center);
    float a = vec3_dot(get_direction(r), get_direction(r));
    float b = 2.0 * vec3_dot(oc, get_direction(r));
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    int hit = (discriminant >= 0);

    if (discriminant >= 0)
        printf("discriminant: %f\n", discriminant);

    //free_vec3(oc);
    return hit;
}

// Function to calculate color for a given ray
struct s_vec3 *ray_color(struct s_ray *r) {
    struct s_vec3 *red = make_vec3(1.0, 0.0, 0.0);
    struct s_vec3 *white = make_vec3(1.0, 1.0, 1.0);
    struct s_vec3 *blue = make_vec3(0.5, 0.7, 1.0);

    if (hit_sphere(make_vec3(0, 0, -1), 0.5, r)) {
        free_vec3(red);
        free_vec3(white);
        return blue;
    }

    struct s_vec3 *unit_direction = vec3_unit_vector(get_direction(r));
    float a = 0.5 * (get_vec3_y(unit_direction) + 1.0);
    struct s_vec3 *result = vec3_add(vec3_mul_float(vec3_sub(white, red), 1.0 - a), vec3_mul_float(blue, a));

    /*free_vec3(red);
    free_vec3(white);
    free_vec3(blue);
    free_vec3(unit_direction);*/

    return result;
}

void draw_circle() {
    // Image
    int image_width = WIDTH;
    int image_height = HEIGHT;

    // Camera
    struct s_vec3 *camera_center = make_vec3(0, 0, 0);
    //float viewport_size = 2.0;

    // Render
    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        printf("\rScanlines remaining: %d ", (image_height - j));
        for (int i = 0; i < image_width; ++i) {
            // Map pixel coordinates to the range [-1, 1]
            float u = (2.0 * i) / (image_width - 1) - 1.0;
            float v = 1.0 - (2.0 * j) / (image_height - 1);

            // Check if the pixel is inside the circle
            if (u * u + v * v <= 1.0) {
                struct s_vec3 *pixel_color = make_vec3(1.0, 0.0, 0.0);  // Red color
                write_color(image, pixel_color);
                //free_vec3(pixel_color);
            } else {
                struct s_vec3 *pixel_color = make_vec3(1.0, 1.0, 1.0);  // White color
                write_color(image, pixel_color);
                //free_vec3(pixel_color);
            }
        }
    }

    printf("\rDone.                 \n");

    fclose(image);

    // Cleanup
    free_vec3(camera_center);
}
