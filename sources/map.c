#include "../includes/cub3d.h"

void init_map(t_data *data)
{
    data->map = (t_map *)malloc(sizeof(t_map));
    int i, j;

    data->map->map_height = 8;

    data->map->map_width = 10;

    // Allocate memory for map_array
    data->map->map_array = (char **)malloc(data->map->map_height * sizeof(char *));
    if (!data->map->map_array)
    {
        // Handle memory allocation failure
        fprintf(stderr, "Error: Memory allocation for map_array failed.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < data->map->map_height; i++)
    {
        data->map->map_array[i] = (char *)malloc(data->map->map_width * sizeof(char));
        if (!data->map->map_array[i])
        {
            // Handle memory allocation failure
            fprintf(stderr, "Error: Memory allocation for map_array row %d failed.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Initialize map_array with values
    char initialMap[8][10] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '1', '1', '1', '0', '0', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

    // Copy values to map_array
    for (i = 0; i < data->map->map_height; i++)
    {
        for (j = 0; j < data->map->map_width; j++)
        {
            data->map->map_array[i][j] = initialMap[i][j];
        }
    }
    draw_map(data);
}

//interate throught the map_array
//offset by map_height*map_width
//each character represents a square
void draw_map(t_data *data)
{
    int square_size = 100; // You need to adjust this based on your requirements
    for (int i = 0; i < data->map->map_height; i++)
    {
        for (int j = 0; j < data->map->map_width; j++)
        {
            if (data->map->map_array[i][j] == '1')
            {
                // Wall - black
                draw_rectangle(j * square_size, (j + 1) * square_size, i * square_size, (i + 1) * square_size, data, BLACK);
            }
            else
            {
                // Empty - white
                draw_rectangle(j * square_size, (j + 1) * square_size, i * square_size, (i + 1) * square_size, data, WHITE);
            }
        }
    }
}
