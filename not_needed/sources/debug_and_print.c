#include "../includes/minirt.h"

void print_vector3(const char *label, t_vector3 *v) {
    printf("%s: (%.2f, %.2f, %.2f)\n", label, v->x, v->y, v->z);
}

void print_color(const char *label, t_color *c) {
    printf("%s: (%u, %u, %u)\n", label, c->r, c->g, c->b);
}

void print_camera(struct s_camera *camera) {
    printf("Camera:\n");
    printf("  Identifier: %s\n", camera->identifier);
    print_vector3("  Position", camera->position);
    print_vector3("  Orientation", camera->orientation);
    printf("  FOV: %.2f\n", camera->fov);
}

void print_light(struct s_light *light) {
    printf("Light:\n");
    printf("  Identifier: %s\n", light->identifier);
    print_vector3("  Position", light->position);
    printf("  Brightness: %.2f\n", light->brightness);
    print_color("  Color", light->color);
}

void print_sphere(struct s_sphere *sphere) {
    printf("Sphere:\n");
    printf("  Identifier: %s\n", sphere->identifier);
    print_vector3("  Center", sphere->center);
    printf("  Diameter: %.2f\n", sphere->diameter);
    print_color("  Color", sphere->color);
}

void print_plane(struct s_plane *plane) {
    printf("Plane:\n");
    printf("  Identifier: %s\n", plane->identifier);
    print_vector3("  Point", plane->point);
    print_vector3("  Normal", plane->normal);
    print_color("  Color", plane->color);
}

void print_cylinder(struct s_cylinder *cylinder) {
    printf("Cylinder:\n");
    printf("  Identifier: %s\n", cylinder->identifier);
    print_vector3("  Center", cylinder->center);
    print_vector3("  Axis", cylinder->axis);
    printf("  Diameter: %.2f\n", cylinder->diameter);
    printf("  Height: %.2f\n", cylinder->height);
    print_color("  Color", cylinder->color);
}

void print_ambient_light(struct s_ambient_light *ambientLight) {
    printf("Ambient Light:\n");
    printf("  Identifier: %s\n", ambientLight->identifier);
    printf("  Ratio: %.2f\n", ambientLight->ratio);
    print_color("  Color", ambientLight->color);
}

void print_scene(struct s_scene *scene) {
    if (scene == NULL) {
        printf("Scene is NULL.\n");
        return;
    }

    print_camera(scene->camera);
    print_light(scene->light);
    print_sphere(scene->sphere);
    print_plane(scene->plane);
    print_cylinder(scene->cylinder);
    print_ambient_light(scene->ambientLight);
}

void test_init_vector()
{
    struct s_vector3 *test_vector = &(struct s_vector3){30, 89, -75};
    print_vector3("test_vector", test_vector);
}