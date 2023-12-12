#include "../includes/minirt.h"

//create the location of the pixel and actually put the image on the screen
void plot_pixel(void *mlx, void *mlx_win, struct s_data *img, int x, int y,  int color)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                 &img->endian);
    my_mlx_pixel_put(img, x, y, color);
    mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}

void my_mlx_pixel_put(struct s_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int init_mlx_keyboard_hook(int keycode, struct s_vars *vars)
{
    printf("start init_mlx_keyboard_hook, keycode: %d\n", keycode);
    if (keycode == 53 && close_window(keycode, vars) == -1)
    {
        printf("failed to close window\n");
        return -1;
    }
    if ((keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2) && mlx_hook_camera_movements(keycode, vars) == -1){
        printf("failed to move camera\n");
        return -1;
    }
    if ((keycode >= 123 && keycode <= 126) && mlx_hook_camera_rotation(keycode, vars) == -1){
        printf("failed to rotate camera\n");
        return -1;
    }
    if ((keycode == 45 || keycode == 46) && mlx_hook_zoom(keycode, vars) == -1){
        printf("failed to zoom camera\n");
        return -1;
    }
    printf("end init_mlx_keyboard_hook\n");

    return 0;
}

int init_mlx_mouse_hook(int keycode, struct s_vars * vars)
{
    (void)vars;
    printf("start mouse_hook, keycode: %d\n", keycode);
    if (keycode == 1)
    {
        printf("left click\n");
    }
    else if (keycode == 2)
    {
        printf("right click\n");
    }
    else if (keycode == 3)
    {
        printf("Middle click\n");
    }
    else if (keycode == 4)
    {
        printf("Scroll up\n");
    }
    else if (keycode == 5)
    {
        printf("Scroll down\n");
    }

    return -1;
}

// Function to initialize the scene structure with default values
void initializeScene(struct s_scene *scene) {
    // Initialize camera
    scene->camera.identifier = "C";
    scene->camera.position = (struct s_vector3){-50.0, 0, 20};
    scene->camera.orientation = (struct s_vector3){0.0, 0.0, 1.0};
    scene->camera.fov = 70.0;

    // Initialize light
    scene->light.identifier = "L";
    scene->light.position = (struct s_vector3){-40.0, 50.0, 0.0};
    scene->light.brightness = 0.6;
    scene->light.color = (struct s_color){10, 0, 255};

    // Initialize sphere
    scene->sphere.identifier = "sp";
    scene->sphere.center = (struct s_vector3){0.0, 0.0, 20.6};
    scene->sphere.diameter = 12.6;
    scene->sphere.color = (struct s_color){10, 0, 255};

    // Initialize plane
    scene->plane.identifier = "pl";
    scene->plane.point = (struct s_vector3){0.0, 0.0, -10.0};
    scene->plane.normal = (struct s_vector3){0.0, 1.0, 0.0};
    scene->plane.color = (struct s_color){0, 0, 225};

    // Initialize cylinder
    scene->cylinder.identifier = "cy";
    scene->cylinder.center = (struct s_vector3){50.0, 0.0, 20.6};
    scene->cylinder.axis = (struct s_vector3){0.0, 0.0, 1.0};
    scene->cylinder.diameter = 14.2;
    scene->cylinder.height = 21.42;
    scene->cylinder.color = (struct s_color){10, 0, 255};

    // Initialize ambient light
    scene->ambientLight.identifier = "A";
    scene->ambientLight.ratio = 0.2;
    scene->ambientLight.color = (struct s_color){255, 255, 255};
}

int main(void)
{
    struct s_vars *vars;
    vars = malloc(sizeof(struct s_vars));
    struct s_data *img = malloc(sizeof(struct s_data));
    struct s_scene myScene;

    if (vars == NULL || img == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    initializeScene(&myScene);

    int window_height = 1920;
    int window_width = 1080;

    vars->mlx = mlx_init();
    if (vars->mlx == NULL) {
        fprintf(stderr, "Failed to initialize MinilibX\n");
        free(vars);
        free(img);
        return 1;
    }

    vars->win = mlx_new_window(vars->mlx, window_height, window_width, "Hello world!");
    if (vars->win == NULL) {
        fprintf(stderr, "Failed to create window\n");
        mlx_destroy_image(vars->mlx, img->img);
        free(vars);
        free(img);
        return 1;
    }

    img->img = mlx_new_image(vars->mlx, window_height, window_width);
    img->height = window_height;
    img->width = window_width;

    mlx_hook(vars->win, 3, 1L << 0, init_mlx_keyboard_hook, vars);
    mlx_mouse_hook(vars->win, init_mlx_mouse_hook, vars);

    printf("Camera Position: %.2f, %.2f, %.2f\n", myScene.camera.position.x, myScene.camera.position.y, myScene.camera.position.z);
    printf("Light Brightness: %.2f\n", myScene.light.brightness);

    mlx_loop(vars->mlx);

    // Cleanup
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_image(vars->mlx, img->img);
    free(vars);
    free(img);

    return 0;
}

