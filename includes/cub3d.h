#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* defining colors */
#define RED 0x00FF0000
#define ORANGE 0x00FFA500
#define YELLOW 0x00FFFF00
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define INDIGO 0x004B0082
#define VIOLET 0x009400D3
#define GREY 0x00CCCCCC
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF

#define PI 3.1415926535
#define FOV 90.0


typedef struct s_player_info
{
    float player_x;
    float player_y;

    float player_delta_x;
    float player_delta_y;
    float player_angle;
}   t_player_info;

typedef struct s_map
{
    int map_height;
    int map_width;
    char **map_array;
    int square_size;
}   t_map;

typedef struct s_data
{
    void *mlx;
    void *mlx_win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int height;
    int width;
    t_player_info *player_1;
    t_map *map;

} t_data;



/* in main.c */
void draw_rectangle(int x_start, int x_end, int y_start, int y_end, t_data *data, int color);
void create_background(int height, int width, t_data data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void start_game(t_data *data);
int main(void);

/* in draw_line.c */
void plotLineLow(int x0, int y0, int x1, int y1, t_data *data, int color);
void plotLineHigh(int x0, int y0, int x1, int y1, t_data *data, int color);
void drawLine(int x0, int y0, int x1, int y1, t_data *data, int color);

/* in player.c */
void draw_player(t_data *data);

/* in events.c */
int	keyevent(int keycode, t_data *data);

/* in map.c */
void init_map(t_data *data);
void draw_map(t_data *data);

/* in draw_rays_3d.c */
void draw_3d_rays(t_data *data);

/* in utils.c */
float degToRad(int a);
int FixAng(int a);

#endif