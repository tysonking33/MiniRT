#include "../includes/cub3d.h"

int keyevent(int keycode, t_data *data)
{
    printf("old player_1->player_x: %f, old player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);
    printf("keycode pressed: %d\n", keycode);

    float new_player_x = data->player_1->player_x;
    float new_player_y = data->player_1->player_y;
    if (keycode == 53)  //esc
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
    else if (keycode == 13) //w
    {
        if (new_player_y - 10.0 > 10.0 && new_player_y - 10.0 < data->width - 10.0)
        {
            new_player_y -= 10.0;
        }
    }
    else if (keycode == 1) //s
    {
        if (new_player_y + 10.0 > 10.0 && new_player_y + 10.0 < data->width - 10.0)
        {
            new_player_y += 10.0;
        }
    }
    else if (keycode == 0) //a
    {
        if (new_player_x - 10.0 > 10.0 && new_player_x - 10.0 < data->height - 10.0)
        {
            new_player_x -= 10.0;
        }
    }
    else if (keycode == 2) //d
    {
        if (new_player_x + 10.0 > 10.0 && new_player_x + 10.0 < data->height - 10.0)
        {
            new_player_x += 10.0;
        }
    }

    printf("new player_1->player_x: %f, new player_1->player_y: %f\n", new_player_x, new_player_y);

    // Update the player's position
    data->player_1->player_x = new_player_x;
    data->player_1->player_y = new_player_y;

    // Redraw the player without redrawing the entire background
    start_game(data);

    return 1;
}