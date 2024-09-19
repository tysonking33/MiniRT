/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tytang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:06:10 by tytang            #+#    #+#             */
/*   Updated: 2022/11/28 12:26:52 by tytang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Data.h"
#include "../includes/Math.h"


// Callback function for key events
// Prints the keycode and exits if the Escape key is pressed
int key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Keycode: %d\n", keycode);  // Print the keycode
	if (keycode == KEY_ESCAPE)          // Check if Escape key is pressed
	{
		printf("Exiting...\n");       // Print exit message
		exit(EXIT_SUCCESS);           // Exit the program
	}
	return (0);
}

// Puts a pixel of a given color at (x, y) in the image
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	// Calculate the address of the pixel and set its color
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Initializes MLX, creates a window, and sets up the image
void initialize_mlx(t_vars *vars, t_data *img, float width, float height)
{
	vars->mlx = mlx_init();                     // Initialize MLX
	vars->win = mlx_new_window(vars->mlx, width, height, "Hello world!"); // Create a new window
	img->img = mlx_new_image(vars->mlx, width, height); // Create a new image
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian); // Get image data address
}

void initalise_data(t_vars *vars,t_data *img, float width, float height)
{
		img->img = mlx_new_image(vars->mlx, width, height); // Create a new image
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian); // Get image data address
}

// Draws a simple example pattern on the image
void draw_example(t_data *img)
{
	// Draw a 2x2 red square
	my_mlx_pixel_put(img, 5, 5, RED);
	my_mlx_pixel_put(img, 15, 15, RED);
	my_mlx_pixel_put(img, 5, 15, RED);
	my_mlx_pixel_put(img, 15, 5, RED);
}

// Main function
int main(void)
{
	float height = 768;  // Window height
	float width = 1366;  // Window width
	t_vars vars;          // MLX and window variables
	t_data img;           // Image data

	initialize_mlx(&vars, &img, width, height); // Initialize MLX and create window and image
	draw_example(&img); // Draw example pattern on the image

	t_data sphere;
	initalise_data(&vars, &sphere, width, height);

	//drawSphere(&sphere);

	renderScene(&sphere);


	mlx_put_image_to_window(vars.mlx, vars.win, sphere.img, 0, 0); // Put image to window

	mlx_key_hook(vars.win, key_hook, &vars); // Set up the key event handler
	mlx_loop(vars.mlx); // Enter the MLX event loop

	return (0); // Return success
}
