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

void drawLine(int x1, int y1, int x2, int y2, t_data *data, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1, y = y1;

    // Determine the sign of dx and dy
    int signX = (dx > 0) ? 1 : -1;
    int signY = (dy > 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    // Calculate decision variable
    int d = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
        // Plot the pixel at (x, y)
        my_mlx_pixel_put(data, x, y, color);

        // Update x and y based on the sign of dx and dy
        x += signX;

        // Update decision variable
        if (d >= 0) {
            y += signY;
            d -= 2 * dx;
        }

        d += 2 * dy;
    }

}


void start_game(t_data *data)
{
    printf("initial player_1->player_x: %f, new player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);

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

    data->player_1->player_x = 50.0;
    data->player_1->player_y = 50.0;
    data->height = 1920;
    data->width = 1080;
        data->player_1->player_x = 300;
        data->player_1->player_y = 300;

    data->player_1->player_delta_x = cos(data->player_1->player_angle) * 5;
        data->player_1->player_delta_y = sin(data->player_1->player_angle) * 5;
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
