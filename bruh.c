#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

typedef struct {
    Vec3 center;
    double radius;
} Sphere;

double dot(Vec3 v1, Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


int hit_sphere(Vec3 *center, double radius, Ray *r, double *t) {
    Vec3 oc = {r->origin.x - center->x, r->origin.y - center->y, r->origin.z - center->z};
    double a = dot(r->direction, r->direction);
    double b = 2.0 * dot(oc, r->direction);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0; // No intersection
    } else {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1; // Intersection
    }
}

Vec3 ray_color(Ray *r) {
    Sphere sphere = {{0, 0, -1}, 0.5};

    double t;
    if (hit_sphere(&sphere.center, sphere.radius, r, &t)) {
        Vec3 N = {r->origin.x + t * r->direction.x - sphere.center.x,
                  r->origin.y + t * r->direction.y - sphere.center.y,
                  r->origin.z + t * r->direction.z - sphere.center.z};
        double len_N = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
        N.x /= len_N;
        N.y /= len_N;
        N.z /= len_N;
        return (Vec3){0.5 * (N.x + 1), 0.5 * (N.y + 1), 0.5 * (N.z + 1)};
    }

    // If no intersection, calculate a background color based on the ray's direction
    Vec3 unit_direction = {r->direction.x, r->direction.y, r->direction.z};
    t = 0.5 * (unit_direction.y + 1.0);
    return (Vec3){(1.0 - t) + t * 0.5, (1.0 - t) + t * 0.7, (1.0 - t) + t * 1.0};
}

void write_color(FILE *file, Vec3 color) {
    fprintf(file, "%d %d %d\n",
            (int)(255.999 * color.x),
            (int)(255.999 * color.y),
            (int)(255.999 * color.z));
}

int main() {
    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    Vec3 lower_left_corner = {-2.0, -1.0, -1.0};
    Vec3 horizontal = {4.0, 0.0, 0.0};
    Vec3 vertical = {0.0, 2.0, 0.0};
    Vec3 origin = {0.0, 0.0, 0.0};

    for (int j = HEIGHT - 1; j >= 0; --j) {
        for (int i = 0; i < WIDTH; ++i) {
            double u = (double)i / (WIDTH - 1);
            double v = (double)j / (HEIGHT - 1);

            Vec3 direction = {lower_left_corner.x + u * horizontal.x + v * vertical.x,
                              lower_left_corner.y + u * horizontal.y + v * vertical.y,
                              lower_left_corner.z + u * horizontal.z + v * vertical.z};

            Ray r = {origin, direction};
            Vec3 color = ray_color(&r);

            write_color(image, color);
        }
    }

    fclose(image);
    return 0;
}
