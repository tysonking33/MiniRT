#include "raytracing.h"

float hit_sphere(struct s_vector *center, float radius, struct s_ray *r) {
    struct s_vector *oc = subtract_vectors(get_origin(r), center);
    float a = dot_product(get_direction(r), get_direction(r));
    float b = 2.0 * dot_product(oc, get_direction(r));
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;

    float result = (discriminant < 0.0) ? -1.0 : (-b - sqrtf(discriminant)) / (2.0 * a);
    printf("result: %f\n", result);
    return result;
}

struct s_vector *ray_color(struct s_ray *r) {
    float t = hit_sphere(make_vector(0.0, 0.0, -1.0), 0.5, r);
    float max_t = 800.0;

    if (t > 0.0 && t < max_t) {
        struct s_vector *N = normalize_vector(subtract_vectors(at(r, t), make_vector(0.0, 0.0, -1.0)));
        struct s_vector *result = multiply_vector_scalar(add_vectors(N, make_vector(1.0, 1.0, 1.0)), 0.5);
        free_vector(N);
        return result;
    }

    struct s_vector *unit_direction = normalize_vector(get_direction(r));
    float a = 0.5 * (get_vector_y(unit_direction) + 1.0);

    struct s_vector *result = add_vectors(
        multiply_vector_scalar(subtract_vectors(make_vector(1.0, 1.0, 1.0), make_vector(0.5, 0.7, 1.0)), 1.0 - a),
        multiply_vector_scalar(make_vector(0.5, 0.7, 1.0), a)
    );

    free_vector(unit_direction);
    return result;
}

void draw_circle() {
    int image_width = WIDTH;
    int image_height = HEIGHT;

    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        printf("\rScanlines remaining: %d ", (image_height - j));
        for (int i = 0; i < image_width; ++i) {
            float u = (2.0 * i) / (image_width - 1.0) - 1.0;
            float v = 1.0 - (2.0 * j) / (image_height - 1.0);

            struct s_ray *ray = make_s_ray(make_vector(0.0, 0.0, 0.0), make_vector(u, v, -1.0));
            struct s_vector *pixel_color = ray_color(ray);

            write_color(image, pixel_color);

            free_s_ray(ray);
            free_vector(pixel_color);
        }
    }

    printf("\rDone.                 \n");
    fclose(image);
}
