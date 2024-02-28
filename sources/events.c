#include "../includes/cub3d.h"

int keyevent(int keycode, t_data *data)
{
    //printf("old player_1->player_x: %f, old player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);
    printf("keycode pressed: %d\n", keycode);

    if (keycode == 53) //esc
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
    else if (keycode == 13) //w
    {
        data->player_1->player_x += data->player_1->player_delta_x;
        data->player_1->player_y += data->player_1->player_delta_y;
    }
    else if (keycode == 1) //s
    {
        data->player_1->player_x -= data->player_1->player_delta_x;
        data->player_1->player_y -= data->player_1->player_delta_y;
    }
    else if (keycode == 0) // a
    {
        data->player_1->player_angle -= 0.1;
        if (data->player_1->player_angle < 0)
        {
            data->player_1->player_angle += 2 * PI;
        }
        // Update player delta values based on the new angle
        data->player_1->player_delta_x = cos(data->player_1->player_angle) * 5;
        data->player_1->player_delta_y = sin(data->player_1->player_angle) * 5;
    }
    else if (keycode == 2) // d
    {
        data->player_1->player_angle += 0.1;
        if (data->player_1->player_angle > 2 * PI)
        {
            data->player_1->player_angle -= 2 * PI;
        }
        // Update player delta values based on the new angle
        data->player_1->player_delta_x = cos(data->player_1->player_angle) * 5;
        data->player_1->player_delta_y = sin(data->player_1->player_angle) * 5;
    }

    printf("player_x: %f, player_y: %f, player_delta_x: %f, player_delta_y: %f\n",
           data->player_1->player_x, data->player_1->player_y, data->player_1->player_delta_x, data->player_1->player_delta_y);

    // Redraw the player without redrawing the entire background
    start_game(data);

    return 1;
}
