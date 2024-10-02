#include "../includes/Data.h"
#include "../includes/Math.h"

// Add these to your t_scene structure or wherever appropriate
float yaw = 0.0f; // Rotation around the Y-axis
float pitch = 0.0f; // Rotation around the X-axis
float ROTATION_SPEED =-10.0f;
float move_scale = 5.0f;

int key_hook(int keycode, t_scene *scene)
{
    printf("Keycode: %d\n", keycode);

    // Define movement variables
    float yaw_radians = yaw * PI / 180.0f;   // Convert yaw to radians
    float pitch_radians = pitch * PI / 180.0f; // Convert pitch to radians

    // Exit on Escape
    if (keycode == KEY_ESCAPE)
    {
        printf("Exiting...\n");
        exit(EXIT_SUCCESS);
    }

    // Left (A) and Right (D) strafe movement
    if (keycode == KEY_D) 
    {
        scene->camera->origin->x += move_scale * cos(yaw_radians) * cos(pitch_radians);
        scene->camera->origin->z += move_scale * sin(yaw_radians) * cos(pitch_radians);
        scene->camera->origin->y += move_scale * sin(pitch_radians);
    }
    else if (keycode == KEY_A) 
    {
        scene->camera->origin->x -= move_scale * cos(yaw_radians) * cos(pitch_radians);
        scene->camera->origin->z -= move_scale * sin(yaw_radians) * cos(pitch_radians);
        scene->camera->origin->y -= move_scale * sin(pitch_radians);
    }

    // Forward (W) and Backwards (S) movement
    if (keycode == KEY_S) 
    {
        scene->camera->origin->x -= move_scale * cos(yaw_radians + PI / 2);
        scene->camera->origin->z -= move_scale * sin(yaw_radians + PI / 2);
    }
    else if (keycode == KEY_W) 
    {
        scene->camera->origin->x += move_scale * cos(yaw_radians + PI / 2);
        scene->camera->origin->z += move_scale * sin(yaw_radians + PI / 2);
    }

    // Move up (N) and down (M)
    if (keycode == KEY_N)
    {
        scene->camera->origin->y += move_scale;
    }
    else if (keycode == KEY_M)
    {
        scene->camera->origin->y -= move_scale;
    }

    // Camera rotation logic
    if (keycode == KEY_LEFT_ARROW) 
    {
        yaw -= ROTATION_SPEED;  // Rotate left
        if (yaw < 0) yaw += 360.0f;  
    }
    else if (keycode == KEY_RIGHT_ARROW) 
    {
        yaw += ROTATION_SPEED;  
        if (yaw > 360.0f) yaw -= 360.0f;
    }

    // Pitch control (Up and Down)
    if (keycode == KEY_UP_ARROW) 
    {
        pitch += ROTATION_SPEED;  
        if (pitch > 89.0f) pitch = 89.0f;  
    }
    else if (keycode == KEY_DOWN_ARROW) 
    {
        pitch -= ROTATION_SPEED;  
        if (pitch < -89.0f) pitch = -89.0f;  
    }

    // Print updated camera position, yaw, and pitch
    printf("Updated Camera Position: (%f, %f, %f)\n", scene->camera->origin->x, scene->camera->origin->y, scene->camera->origin->z);
    printf("Updated Yaw: %f, Pitch: %f\n", yaw, pitch);
    //renderSceneSphere(scene->data, scene); // Render the scene
    renderScenePlane(scene->data, scene);

    mlx_put_image_to_window(scene->vars->mlx, scene->vars->win, scene->data->img, 0, 0); // Put image to window

    return 0;
}

// Puts a pixel of a given color at (x, y) in the image
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    // Calculate the address of the pixel and set its color
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void initalise_data(t_vars **vars, t_data **img, float width, float height)
{
    (*img)->img = mlx_new_image((*vars)->mlx, width, height);
    (*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
}

// Initializes the scene and allocates memory
void initialize_mlx(t_vars **vars, t_data **img, float width, float height)
{
    *vars = (t_vars *)malloc(sizeof(t_vars));
    if (*vars == NULL) {
        fprintf(stderr, "vars Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*vars)->mlx = mlx_init();
    if ((*vars)->mlx == NULL) {
        fprintf(stderr, "vars->mlx Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*vars)->win = mlx_new_window((*vars)->mlx, width, height, "Hello world!");
    if ((*vars)->win == NULL) {
        fprintf(stderr, "vars->win Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *img = (t_data *)malloc(sizeof(t_data));
    if (*img == NULL) {
        fprintf(stderr, "img Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*img)->img = mlx_new_image((*vars)->mlx, width, height);
    if ((*img)->img == NULL) {
        fprintf(stderr, "img->img Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    (*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
    if ((*img)->addr == NULL) {
        fprintf(stderr, "img->addr Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void initialize_scene_elements(t_scene *scene)
{
    int num_spheres = 2;
    // Allocate memory for camera, light, and sphere
    scene->camera = (t_ray *)malloc(sizeof(t_ray));
    scene->light = (t_ray *)malloc(sizeof(t_ray));
    scene->sphere = (t_sphere *)malloc(num_spheres * sizeof(t_sphere)); 
    for (int i = 0; i < num_spheres; i++)
    {
        scene->sphere->origin = (t_vec3 *)malloc(sizeof(t_vec3));
    }

    if (!scene->camera || !scene->light || !scene->sphere) {
        fprintf(stderr, "Camera/Light/Sphere Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for origins and directions
    scene->camera->origin = (t_vec3 *)malloc(sizeof(t_vec3));
    scene->camera->direction = (t_vec3 *)malloc(sizeof(t_vec3));
    scene->light->origin = (t_vec3 *)malloc(sizeof(t_vec3));
    scene->light->direction = (t_vec3 *)malloc(sizeof(t_vec3));
    scene->sphere->origin = (t_vec3 *)malloc(sizeof(t_vec3)); // Allocate memory for sphere's origin

    if (!scene->camera->origin || !scene->camera->direction ||
        !scene->light->origin || !scene->light->direction ||
        !scene->sphere->origin) { // Check for sphere's origin allocation
        fprintf(stderr, "Ray origin/direction Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    scene->camera->origin->x = 0.0f;
    scene->camera->origin->y = 0.0f;
    scene->camera->origin->z = -50.0f; 

    scene->camera->direction->x = 0.0f;
    scene->camera->direction->y = 0.0f;
    scene->camera->direction->z = 1.0f; 

    t_sphere *sphere0 = (t_sphere*)malloc(sizeof(t_sphere));
    sphere0->origin = (t_vec3 *)malloc(sizeof(t_vec3));
    *(sphere0->origin) = createVec3(0, 0, 0); 
    sphere0->radius = 10.0f; 

    t_sphere *sphere1 = (t_sphere *)malloc(sizeof(t_sphere));
    sphere1->origin = (t_vec3 *)malloc(sizeof(t_vec3));
    *(sphere1->origin) = createVec3(20, 0, 0); 
    sphere1->radius = 10.0f; 

    scene->sphere[0] = *sphere0;
    scene->sphere[1] = *sphere1;
    scene->num_spheres = num_spheres;
    
    
    scene->light->origin->x = 0.0f;
    scene->light->origin->y = 5.0f; 
    scene->light->origin->z = -20.0f;
    scene->fov = 90.0f;



    scene->num_planes = 1;

    t_plane *plane1 = (t_plane*)malloc(sizeof(t_plane));
    plane1->origin = (t_vec3*)malloc(sizeof(t_vec3));
    *plane1->origin = createVec3(0,0,0);
    plane1->normal = (t_vec3*)malloc(sizeof(t_vec3));
    plane1->P1 = (t_vec3*)malloc(sizeof(t_vec3));
    plane1->P2 = (t_vec3*)malloc(sizeof(t_vec3));
    plane1->P3 = (t_vec3*)malloc(sizeof(t_vec3));
    plane1->P4 = (t_vec3*)malloc(sizeof(t_vec3));
    plane1->base_color = (t_vec3*)malloc(sizeof(t_vec3));               //base color is red
    plane1->base_color->x = 1.0f;
    plane1->base_color->y = 0.0f;
    plane1->base_color->z = 0.0f;
    plane1->height = 10.0f;
    plane1->width = 10.0f;

    float halfWidth  =plane1->width / 2;
    float halfHeight  =plane1->height / 2;

    //top left
    plane1->P1->x = plane1->origin->x - halfWidth;
    plane1->P1->y = plane1->origin->y + halfHeight;
    plane1->P1->z = plane1->origin->z;    

    //top right
    plane1->P2->x = plane1->origin->x + halfWidth;
    plane1->P2->y = plane1->origin->y + halfHeight;
    plane1->P2->z = plane1->origin->z;  

    //bottom left
    plane1->P3->x = plane1->origin->x - halfWidth;
    plane1->P3->y = plane1->origin->y - halfHeight;
    plane1->P3->z = plane1->origin->z;    

    //bottom right
    plane1->P4->x = plane1->origin->x + halfWidth;
    plane1->P4->y = plane1->origin->y - halfHeight;
    plane1->P4->z = plane1->origin->z;    

    t_vec3 v1 = vec3_sub(*plane1->P2, *plane1->P1);
    t_vec3 v2 = vec3_sub(*plane1->P3, *plane1->P1);

    crossProduct(&v1, &v2, plane1->normal);
    normalise(plane1->normal);

    scene->plane = (t_plane *)malloc(scene->num_planes *sizeof(t_plane));
    scene->plane[0] = *plane1;


}

void crossProduct(t_vec3 *a, t_vec3 *b, t_vec3 *result)
{
    result->x = a->y * b->z - a->z * b->y; 
    result->y = a->z * b->x - a->x * b->z; 
    result->z = a->x * b->y - a->y * b->x; 
}

void normalise(t_vec3 *result)
{
    float length = sqrt(result->x * result->x + result->y * result->y + result->z * result->z);
    if (length != 0.0f)
    {
        result->x /= length;
        result->y /= length;
        result->z /= length;
    }
}

// Main function
int main(void)
{
    float height = 768; // Window height
    float width = 1366; // Window width
    t_scene *sceneObj = (t_scene *)malloc(sizeof(t_scene));
    if (sceneObj == NULL) {
        fprintf(stderr, "sceneObj Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize scene dimensions
    sceneObj->height = height;
    sceneObj->width = width;

    // Initialize MLX and data
    initialize_mlx(&sceneObj->vars, &sceneObj->data, width, height);
    initalise_data(&sceneObj->vars, &sceneObj->data, width, height);

    // Initialize scene elements (camera, light, sphere)
    initialize_scene_elements(sceneObj);

    //renderSceneSphere(sceneObj->data, sceneObj); // Render the scene
    renderScenePlane(sceneObj->data, sceneObj);

    mlx_put_image_to_window(sceneObj->vars->mlx, sceneObj->vars->win, sceneObj->data->img, 0, 0); // Put image to window

    mlx_key_hook(sceneObj->vars->win, key_hook, sceneObj); // Set up the key event handler
    mlx_loop(sceneObj->vars->mlx); // Enter the MLX event loop

    // Free allocated memory
    free(sceneObj->camera->origin);
    free(sceneObj->camera->direction);
    free(sceneObj->camera);
    free(sceneObj->light->origin);
    free(sceneObj->light->direction);
    free(sceneObj->light);
    free(sceneObj->sphere->origin); // If needed
    free(sceneObj->sphere);
    free(sceneObj->data);
    free(sceneObj->vars);
    free(sceneObj);

    return (0); // Return success
}
