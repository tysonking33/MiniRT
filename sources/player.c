#include "../includes/cub3d.h"

void draw_player(t_data *data)
{
    int start_x = (int)(data->player_1->player_x - 5);
    int end_x = (int)(data->player_1->player_x + 5);
    int start_y = (int)(data->player_1->player_y - 5);
    int end_y = (int)(data->player_1->player_y + 5);

    // Clear the screen (draw background)
    create_background(data->height, data->width, *data);

    // Draw the 2D map with updated player position and rotation
    draw_map(data);

    // Draw the player on the 2D map
    draw_rectangle(start_x, end_x, start_y, end_y, data, YELLOW);

    // Draw the 3D rays
    draw_3d_rays(data);

    // Update the window with the new content
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

    // Print the updated player information (optional)
    printf("player_x: %f, player_y: %f, player_delta_x: %f, player_delta_y: %f\n", 
        data->player_1->player_x, data->player_1->player_y, data->player_1->player_delta_x,
        data->player_1->player_delta_y);
}
