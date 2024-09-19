#ifndef DATA_H
#define DATA_H

#include "../mlx_linux/mlx.h"
#include "./Window_Keys.h"
#include "./Colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

float height = 768; // Window height
float width = 1366; // Window width

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
    struct s_vec3 *origin;
    struct s_vec3 *direction;
} t_ray;

typedef struct s_vec3
{
    float x;
    float y;
    float z;
} t_vec3;

typedef struct s_sphere
{
    struct s_vec3 *origin;
    float radius;
} t_sphere;

// Function prototypes

/*-------------------------------main.c---------------------------------------------------------*/
int key_hook(int keycode, t_vars *vars);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void initialize_mlx(t_vars *vars, t_data *img, float width, float height);
void draw_example(t_data *img);
void initalise_data(t_vars *vars, t_data *img, float width, float height);

/*-------------------------------sphere.c--------------------------------------------------------*/
uint32_t rgbaToHex(struct s_vec3 color);
void renderScene(t_data *img);
struct s_vec3 generateRayDirection(int px, int py, float width, float height, float fov);
struct s_vec3 raytraceSphere(struct s_ray ray, struct s_vec3 lightOrigin);
uint32_t rgbaToHex(struct s_vec3 color);

/*-------------------------------generic_sphere.c--------------------------------------------------------*/
void plotHorizontalLine(int x1, int x2, int y, t_data *img);
void drawFilledCircle(int xc, int yc, int r, t_data *img);
void drawSphere(t_data *img);

#endif