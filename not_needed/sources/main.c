#include "../includes/minirt.h"

// Function to plot a pixel
void plot_pixel(void *mlx, void *mlx_win, struct s_data *img, int x, int y, int color)
{

    // Ensure img->img is a valid image structure created with mlx_new_image
    if (img->img == NULL)
    {
        //printf("Error: Invalid image structure.\n");
        return;
    }
    else
    {
        //printf("seg a\n");
    }

    
    // Get image data address
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    if (img->addr == NULL)
    {
        //printf(stderr, "Error: Failed to get image data address.\n");
        return;
    }

    my_mlx_pixel_put(img, x, y, color);
    //printf("seg c\n");

    // Put the image to the window
    mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
    //printf("seg d\n");
}

void my_mlx_pixel_put(struct s_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int init_mlx_keyboard_hook(int keycode, struct s_vars *vars)
{
    //printf("start init_mlx_keyboard_hook, keycode: %d\n", keycode);
    if (keycode == 53 && close_window(keycode, vars) == -1)
    {
        //printf("failed to close window\n");
        return -1;
    }
    if ((keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2) && mlx_hook_camera_movements(keycode, vars) == -1)
    {
        //printf("failed to move camera\n");
        return -1;
    }
    if ((keycode >= 123 && keycode <= 126) && mlx_hook_camera_rotation(keycode, vars) == -1)
    {
        //printf("failed to rotate camera\n");
        return -1;
    }
    if ((keycode == 45 || keycode == 46) && mlx_hook_zoom(keycode, vars) == -1)
    {
        //printf("failed to zoom camera\n");
        return -1;
    }
    //printf("end init_mlx_keyboard_hook\n");

    return 0;
}

int init_mlx_mouse_hook(int keycode, struct s_vars *vars)
{
    (void)vars;
    //printf("start mouse_hook, keycode: %d\n", keycode);
    if (keycode == 1)
    {
        //printf("left click\n");
    }
    else if (keycode == 2)
    {
        //printf("right click\n");
    }
    else if (keycode == 3)
    {
        //printf("Middle click\n");
    }
    else if (keycode == 4)
    {
        //printf("Scroll up\n");
    }
    else if (keycode == 5)
    {
        //printf("Scroll down\n");
    }

    return -1;
}

void initializeScene(struct s_scene *scene)
{
    // Allocate memory for each structure before assigning values
    scene->camera = malloc(sizeof(struct s_camera));
    scene->light = malloc(sizeof(struct s_light));
    scene->sphere = malloc(sizeof(struct s_sphere));
    scene->plane = malloc(sizeof(struct s_plane));
    scene->cylinder = malloc(sizeof(struct s_cylinder));
    scene->ambientLight = malloc(sizeof(struct s_ambient_light));

    // Initialize camera
    scene->camera->identifier = "C";
    scene->camera->position = malloc(sizeof(struct s_vector3));
    scene->camera->position->x = 50.0;
    scene->camera->position->y = 0.0;
    scene->camera->position->z = 20.0;
    scene->camera->orientation = malloc(sizeof(struct s_vector3));
    scene->camera->orientation->x = 0.0;
    scene->camera->orientation->y = 0.0;
    scene->camera->orientation->z = 1.0;
    scene->camera->fov = 70.0;

    // Initialize light
    scene->light->identifier = "L";
    scene->light->position = malloc(sizeof(struct s_vector3));
    scene->light->position->x = -40.0;
    scene->light->position->y = 0.0;
    scene->light->position->z = 30.0;
    scene->light->brightness = 0.7;
    scene->light->color = malloc(sizeof(struct s_color));
    scene->light->color->r = 255;
    scene->light->color->g = 255;
    scene->light->color->b = 255;

    // Initialize sphere
    scene->sphere->identifier = "sp";
    scene->sphere->center = malloc(sizeof(struct s_vector3));
    scene->sphere->center->x = 0.0;
    scene->sphere->center->y = 0.0;
    scene->sphere->center->z = 20.0;
    scene->sphere->diameter = 20.0;
    scene->sphere->color = malloc(sizeof(struct s_color));
    scene->sphere->color->r = 255;
    scene->sphere->color->g = 0;
    scene->sphere->color->b = 0;

    // Initialize plane
    scene->plane->identifier = "pl";
    scene->plane->point = malloc(sizeof(struct s_vector3));
    scene->plane->point->x = 0.0;
    scene->plane->point->y = 0.0;
    scene->plane->point->z = 0.0;
    scene->plane->normal = malloc(sizeof(struct s_vector3));
    scene->plane->normal->x = 0.0;
    scene->plane->normal->y = 1.0;
    scene->plane->normal->z = 0.0;
    scene->plane->color = malloc(sizeof(struct s_color));
    scene->plane->color->r = 255;
    scene->plane->color->g = 0;
    scene->plane->color->b = 225;

    // Initialize cylinder
    scene->cylinder->identifier = "cy";
    scene->cylinder->center = malloc(sizeof(struct s_vector3));
    scene->cylinder->center->x = 50.0;
    scene->cylinder->center->y = 0.0;
    scene->cylinder->center->z = 20.6;
    scene->cylinder->axis = malloc(sizeof(struct s_vector3));
    scene->cylinder->axis->x = 0.0;
    scene->cylinder->axis->y = 0.0;
    scene->cylinder->axis->z = 1.0;
    scene->cylinder->diameter = 14.2;
    scene->cylinder->height = 21.42;
    scene->cylinder->color = malloc(sizeof(struct s_color));
    scene->cylinder->color->r = 10;
    scene->cylinder->color->g = 0;
    scene->cylinder->color->b = 255;

    // Initialize ambient light
    scene->ambientLight->identifier = "A";
    scene->ambientLight->ratio = 0.2;
    scene->ambientLight->color = malloc(sizeof(struct s_color));
    scene->ambientLight->color->r = 255;
    scene->ambientLight->color->g = 255;
    scene->ambientLight->color->b = 255;
}



struct s_ray *initializeCameraRay(struct s_camera *camera)
{
    struct s_ray *camera_ray = malloc(sizeof(struct s_ray));

    // Allocate memory for direction and origin
    camera_ray->direction = malloc(sizeof(struct s_vector3));
    camera_ray->origin = malloc(sizeof(struct s_vector3));

    // Copy values from camera to ray
    camera_ray->origin->x = camera->position->x;
    camera_ray->origin->y = camera->position->y;
    camera_ray->origin->z = camera->position->z;

    // Calculate direction based on the difference between the orientation and position
    camera_ray->direction->x = camera->orientation->x - camera->position->x;
    camera_ray->direction->y = camera->orientation->y - camera->position->y;
    camera_ray->direction->z = camera->orientation->z - camera->position->z;

    // Normalize the direction vector
    camera_ray->direction = normalize(camera_ray->direction);

    return camera_ray;
}



void cleanup_scene(struct s_scene *scene)
{
    free(scene->camera->position);
    free(scene->camera->orientation);
    free(scene->camera);

    free(scene->light->position);
    free(scene->light->color);
    free(scene->light);

    free(scene->sphere->center);
    free(scene->sphere->color);
    free(scene->sphere);

    free(scene->plane->point);
    free(scene->plane->normal);
    free(scene->plane->color);
    free(scene->plane);

    free(scene->cylinder->center);
    free(scene->cylinder->axis);
    free(scene->cylinder->color);
    free(scene->cylinder);

    free(scene->ambientLight->color);
    free(scene->ambientLight);
}

void cleanup_data(struct s_data *data)
{
    // Free memory associated with mlx_and_win
    if (data->mlx_and_win != NULL)
    {
        // Free memory associated with mlx_and_win->mlx
        if (data->mlx_and_win->mlx != NULL)
        {
            mlx_do_sync(data->mlx_and_win->mlx); // Sync before destroying display
            free(data->mlx_and_win->mlx);
            data->mlx_and_win->mlx = NULL;
        }

        // Free memory associated with mlx_and_win->win
        if (data->mlx_and_win->win != NULL)
        {
            free(data->mlx_and_win->win);
            data->mlx_and_win->win = NULL;
        }

        // Free memory associated with mlx_and_win
        free(data->mlx_and_win);
        data->mlx_and_win = NULL;
    }

    // Free memory associated with img
    if (data->img != NULL)
    {
        mlx_destroy_image(data->mlx_and_win->mlx, data->img);
        data->img = NULL;
    }

    // Additional cleanup for other members if needed

    // Set other members to default values or free associated memory if needed
    data->addr = NULL;
    data->bits_per_pixel = 0;
    data->line_length = 0;
    data->endian = 0;
    data->height = 0.0;
    data->width = 0.0;
}


int main(void)
{
    struct s_data *data = malloc(sizeof(struct s_data));
    data->mlx_and_win = malloc(sizeof(struct s_vars));
    struct s_scene *myScene = malloc(sizeof(struct s_scene));

    if (data == NULL || data->mlx_and_win == NULL || myScene == NULL)
    {
        //printf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    data->width = 1920;
    data->height = 1080;


    data->width = 200;
    data->height = 200;

    initializeScene(myScene);

    data->mlx_and_win->mlx = mlx_init();

    // Ensure that the window size is set appropriately
    data->mlx_and_win->win = mlx_new_window(data->mlx_and_win->mlx, data->width, data->height, "My Window");

    // Check if the window creation is successful
    if (data->mlx_and_win->win == NULL)
    {
        //printf(stderr, "Error: Failed to create window.\n");
        return 1;
    }

    // Set up hooks
    mlx_hook(data->mlx_and_win->win, 3, 1L << 0, init_mlx_keyboard_hook, data->mlx_and_win);
    mlx_mouse_hook(data->mlx_and_win->win, init_mlx_mouse_hook, data->mlx_and_win);

    // Begin drawing
    data->img = mlx_new_image(data->mlx_and_win->mlx, data->width, data->height);

    //begin_drawing(myScene, data);

    //draw_blue_to_white(myScene, data, data->mlx_and_win->mlx, data->mlx_and_win->win);
    draw_sphere(myScene, data, data->mlx_and_win->mlx, data->mlx_and_win->win);

    // Start the event loop
    mlx_loop(data->mlx_and_win->mlx);

    // Cleanup code...
    cleanup_scene(myScene);
    cleanup_data(data);


    return 0;
}