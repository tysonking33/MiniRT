#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* defining colors */
#define RED 0x00FF0000
#define ORANGE 0x00FFA500
#define YELLOW 0x00FFFF00
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define INDIGO 0x004B0082
#define VIOLET 0x009400D3
#define GREY 0x00CCCCCC

typedef struct s_player_info
{
    float player_x;
    float player_y;
}   t_player_info;   

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
} t_data;



/* in main.c */
void draw_rectangle(int x_start, int x_end, int y_start, int y_end, t_data img, int color);
void create_background(int height, int width, t_data img);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void start_game(t_data *data);
int main(void);


/* in player.c */
void draw_player(t_data *data);

/* in events.c */
int	keyevent(int keycode, t_data *data);

#endif