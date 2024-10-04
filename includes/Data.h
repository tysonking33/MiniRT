#ifndef DATA_H
#define DATA_H

#include "../mlx_linux/mlx.h"
#include "./Window_Keys.h"
#include "./Colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

typedef struct s_vec3
{
    float x;
    float y;
    float z;
} t_vec3;

// Structure to hold image data
typedef struct s_data
{
    void *img;          // Pointer to the image
    char *addr;         // Pointer to the image's pixel data
    int bits_per_pixel; // Bits per pixel of the image
    int line_length;    // Length of a line in bytes
    int endian;         // Endianness of the image
} t_data;

// Structure to hold window and MLX data
typedef struct s_vars
{
    void *mlx; // Pointer to the MLX instance
    void *win; // Pointer to the window
} t_vars;

typedef struct s_ray
{
    t_vec3 *origin;
    t_vec3 *direction;
} t_ray;

typedef struct s_sphere
{
    t_vec3 *origin;
    float radius;
} t_sphere;

typedef struct s_plane
{
    t_vec3 *origin;
    t_vec3 *normal;

    /*------------plane corners------------------*/
    t_vec3 *P1;
    t_vec3 *P2;
    t_vec3 *P3;
    t_vec3 *P4;

    /*---------------properties----------------------------*/

    t_vec3 *base_color;
    float height;
    float width;
} t_plane;

typedef struct s_cylinder
{
    t_vec3 *origin;
    float radius;
    float height;
    t_vec3 *normal;
} t_cylinder;

typedef struct s_scene
{
    t_ray *camera;
    t_ray *light;
    float fov;
    float width;
    float height;
    t_sphere *sphere;
    int num_spheres;
    t_data *data;
    t_vars *vars;
    t_plane *plane;
    int num_planes;

    t_cylinder *cylinder;
    int num_cylinder;
} t_scene;

// Function prototypes

/*-------------------------------main.c---------------------------------------------------------*/
int key_hook(int keycode, t_scene *scene);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void initialize_mlx(t_vars **vars, t_data **img, float width, float height);
void draw_example(t_data *img);
void initalise_data(t_vars **vars, t_data **img, float width, float height);
void updateScene(t_scene *sceneObj);
void clear_screen_to_black(t_scene *sceneObj);
void crossProduct(t_vec3 *a, t_vec3 *b, t_vec3 *result);
void normalise(t_vec3 *result);
void initialize_planes(t_scene *scene, int num_planes);
void initialize_spheres(t_scene *scene, int num_spheres);
void initialize_cylinder(t_scene *scene, int num_cylinder);

/*-------------------------------sphere.c--------------------------------------------------------*/
uint32_t rgbaToHex(t_vec3 color);
void renderSceneSphere(t_data *img, t_scene *sceneObj);
t_vec3 generateRayDirection(int x, int y, t_scene *scene);
t_vec3 raytraceSphere(struct s_ray ray, t_sphere sphereObj, t_ray *lightObj);
uint32_t rgbaToHex(t_vec3 color);
t_vec3 computeSphereObjNormal(t_vec3 intersectionPoint, t_sphere sphere);
t_vec3 computeSphereNormal(t_vec3 intersection, t_sphere sphere);
int raySphereIntersect(t_ray *ray, t_sphere *sphere, float *t);

/*-------------------------------generic_sphere.c--------------------------------------------------------*/
void plotHorizontalLine(int x1, int x2, int y, t_data *img);
void drawFilledCircle(int xc, int yc, int r, t_data *img);
void drawSphere(t_data *img);

/*-------------------------------plane.c--------------------------------------------------------*/
void renderScenePlane(t_data *img, t_scene *scene);
int rayPlaneIntersect(t_ray *ray, t_plane *plane, float *t);
int checkIfBounded(t_ray *ray, t_plane *plane, float t);
t_vec3 raytracePlane(t_ray ray, t_plane plane, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint);
t_vec3 vec3_mult(t_vec3 v1, t_vec3 v2);
t_vec3 calculateShadow(t_ray ray, t_plane plane, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint);

/*-------------------------------cylinder.c--------------------------------------------------------*/
void renderSceneCylinder(t_data *img, t_scene *scene);
int rayCylinderIntersect(t_ray *ray, t_cylinder *cylinder, float *t);
void findSurfaceNormal(t_scene *sceneObj, t_vec3 *intersectionPoint, t_cylinder *cylinder);
t_vec3 raytraceCylinder(t_ray ray, t_cylinder cylinder, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint);
#endif