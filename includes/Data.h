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

typedef struct s_scene
{
    t_ray * camera;
    t_ray * light;
    float fov;
    float width;
    float height;
    t_sphere *sphere;
    int num_spheres;
    t_data *data;
    t_vars *vars;
}   t_scene;

// Function prototypes

/*-------------------------------main.c---------------------------------------------------------*/
int key_hook(int keycode, t_scene *scene);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void initialize_mlx(t_vars **vars, t_data **img, float width, float height);
void draw_example(t_data *img);
void initalise_data(t_vars **vars, t_data **img, float width, float height);
//void initalise_scene(t_scene *sceneObj, float height, float width);
void updateScene(t_scene *sceneObj);
void clear_screen_to_black(t_scene *sceneObj);

/*-------------------------------sphere.c--------------------------------------------------------*/
uint32_t rgbaToHex(t_vec3 color);
void renderScene(t_data *img, t_scene *sceneObj);
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

#endif