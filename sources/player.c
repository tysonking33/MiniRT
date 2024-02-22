#include "../includes/cub3d.h"

void draw_player(t_data *data)
{
    printf("draw_player player_1->player_x: %f, new player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);

    int start_x = (int)(data->player_1->player_x - 5);
    int end_x = (int)(data->player_1->player_x + 5);
    int start_y = (int)(data->player_1->player_y - 5);
    int end_y = (int)(data->player_1->player_y + 5);
    draw_rectangle(start_x, end_x, start_y, end_y, *data, YELLOW);


    int start_x1 = (int)(data->player_1->player_x -4 );
    int end_x1 = (int)(data->player_1->player_x +6);
    int start_y1 = (int)(data->player_1->player_y - 4);
    int end_y1 = (int)(data->player_1->player_y + 6);
    draw_rectangle(start_x1, end_x1, start_y1, end_y1, *data, RED);
}
