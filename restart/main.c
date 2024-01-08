

#include "minirt.h"



int main(int argc, char **argv) {
    numSpheres = 0;
    imageWidth = 640;
    imageHeight = 480;

    struct s_spheres *sphere_struct_vector = NULL; // Initialize to NULL




    sphere_struct_vector = insert_spheres(sphere_struct_vector);

    print_sphere_struct(sphere_struct_vector);

    struct s_camera myCamera = {
        .eyePosition = {0.0, 0.0, 0.0},
        .lookAt = {0.0, 0.0, -1.0},
        .upVector = {0.0, 1.0, 0.0},
        .fov = 60.0
    };

    struct s_object *object_vector = (struct s_object*)malloc(sizeof(struct s_object));
    object_vector->sphere = sphere_struct_vector;

    start_raytracing(object_vector, &myCamera);
    
    clean_sphere_vector(sphere_struct_vector);

    return 0;
}
