#include "../includes/cub3d.h"

void draw_player(t_data *data)
{
    //printf("draw_player player_1->player_x: %f, new player_1->player_y: %f\n", data->player_1->player_x, data->player_1->player_y);

    int start_x = (int)(data->player_1->player_x - 5);
    int end_x = (int)(data->player_1->player_x + 5);
    int start_y = (int)(data->player_1->player_y - 5);
    int end_y = (int)(data->player_1->player_y + 5);
    draw_rectangle(start_x, end_x, start_y, end_y, data, YELLOW);

    drawLine(data->player_1->player_x, data->player_1->player_y, data->player_1->player_x+data->player_1->player_delta_x*20, data->player_1->player_y+data->player_1->player_delta_y*20, data, RED);

    printf("data->player_1->player_x+data->player_1->player_delta_x*20: %f, data->player_1->player_y+data->player_1->player_delta_y*20: %f\n",
    data->player_1->player_x+data->player_1->player_delta_x*20, data->player_1->player_y+data->player_1->player_delta_y*20);

}
