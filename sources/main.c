#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void create_background(int height, int width, t_data data)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            my_mlx_pixel_put(&data, i, j, GREY);
        }
    }
}

void draw_rectangle(int x_start, int x_end, int y_start, int y_end, t_data *data, int color)
{
    for (int i = x_start; i < x_end; i++)
    {
        for (int j = y_start; j < y_end; j++)
        {
            my_mlx_pixel_put(data, i, j, color);
        }
    }
}

void plotLineLow(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        my_mlx_pixel_put(data, x, y, color);
        if (D > 0)
        {    y += yi;
            D += 2 * (dy - dx);
        }
        else
        {
            D += 2*dy;
        }
        
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;

    for (int y =  y0; y <= y1; y++)
    {
        my_mlx_pixel_put(data, x, y, color);
        if (D > 0)
        {
            x += xi;
            D += (2 *(dx - dy));
        }
        else
        {
            D += 2*dx;
        }
        
    }
}


void drawLine(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
            plotLineLow(x1, y1, x0, y0, data, color);
        else
            plotLineLow(x0, y0, x1, y1, data, color);
    }
    else
    {
        if (y0 > y1)
            plotLineHigh(x1, y1, x0, y0, data, color);
        else
            plotLineHigh(x0, y0, x1, y1, data, color);

    }
}


void start_game(t_data *data)
{
    //printf("initial player_1->player_x: %f, new player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);

    // Initialize img properly
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

    create_background(data->height, data->width, *data);
    init_map(data);


    draw_player(data);

    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}


int main(void)
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return -1; // Check for successful memory allocation

    data->player_1 = (t_player_info *)malloc(sizeof(t_player_info));
    if (!data->player_1)
    {
        free(data); // Free memory in case of failure
        return -1;
    }


    data->height = 1500;
    data->width = 1080;
    data->player_1->player_x = 300;
    data->player_1->player_y = 300;
    data->player_1->player_angle = 0;

    data->player_1->player_delta_x = cos(data->player_1->player_angle) * 5;
    data->player_1->player_delta_y = sin(data->player_1->player_angle) * 5;
    /*printf("(main) player_x: %f, player_y: %f, player_delta_x: %f, player_delta_y: %f\n", 
        data->player_1->player_x, data->player_1->player_y, data->player_1->player_delta_x
        ,data->player_1->player_delta_y);*/
    data->mlx = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx, data->height, data->width, "Hello world!");

    

    // Initialize img properly
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

    start_game(data);
    mlx_hook(data->mlx_win, 2, 3, keyevent, data);
    mlx_loop(data->mlx);

    // Don't forget to free allocated memory before exiting
    free(data->player_1);
    free(data);

    return 0;
}
