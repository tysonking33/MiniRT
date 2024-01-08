
#include "minirt.h"

// Function to push a new sphere to the vector and update its size
struct s_spheres *sphere_push_back(struct s_spheres *sphere_struct_vector, struct s_spheres *new_sphere)
{
    // Increase the size of the array
    numSpheres += 1;
    sphere_struct_vector = realloc(sphere_struct_vector, (numSpheres) * sizeof(struct s_spheres));

    if (sphere_struct_vector == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Copy the new sphere's data to the end of the array
    sphere_struct_vector[numSpheres - 1] = *new_sphere;
    return sphere_struct_vector; // Return the updated array
}

// Function to print information about all spheres in the vector
void print_sphere_struct(struct s_spheres *sphere_struct_vector)
{
    for (int i = 0; i < numSpheres; i++)
    {
        printf("Sphere %d:\n", i + 1);
        printf("  Center: %.2f, %.2f, %.2f\n", sphere_struct_vector[i].center->x, sphere_struct_vector[i].center->y, sphere_struct_vector[i].center->z);
        printf("  Radius: %.2f\n", sphere_struct_vector[i].radius);
        printf("  Surface Color: %.2f, %.2f, %.2f\n", sphere_struct_vector[i].surfaceColor->x, sphere_struct_vector[i].surfaceColor->y, sphere_struct_vector[i].surfaceColor->z);
        printf("  Emission Color: %.2f, %.2f, %.2f\n", sphere_struct_vector[i].emissionColor->x, sphere_struct_vector[i].emissionColor->y, sphere_struct_vector[i].emissionColor->z);
        printf("  Transparency: %.2f\n", sphere_struct_vector[i].transparency);
        printf("  Reflection: %.2f\n", sphere_struct_vector[i].reflection);
        printf("\n");
    }
}

// Function to insert predefined spheres into the vector
struct s_spheres *insert_spheres(struct s_spheres *sphere_struct_vector)
{
    // Sphere 1
    struct s_spheres *new_sphere1 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere1->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere1->center->x = 0.0;
    new_sphere1->center->y = -10004.0;
    new_sphere1->center->z = -20.0;
    new_sphere1->radius = 10000.0;
    new_sphere1->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere1->surfaceColor->x = 0.20;
    new_sphere1->surfaceColor->y = 0.20;
    new_sphere1->surfaceColor->z = 0.20;
    new_sphere1->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere1->emissionColor->x = 0.0;
    new_sphere1->emissionColor->y = 0.0;
    new_sphere1->emissionColor->z = 0.0;
    new_sphere1->transparency = 0.0;
    new_sphere1->reflection = 0.0;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere1);

    // Sphere 2
    struct s_spheres *new_sphere2 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere2->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere2->center->x = 0.0;
    new_sphere2->center->y = 0.0;
    new_sphere2->center->z = -20.0;
    new_sphere2->radius = 4.0;
    new_sphere2->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere2->surfaceColor->x = 1.00;
    new_sphere2->surfaceColor->y = 0.32;
    new_sphere2->surfaceColor->z = 0.36;
    new_sphere2->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere2->emissionColor->x = 0.0;
    new_sphere2->emissionColor->y = 0.5;
    new_sphere2->emissionColor->z = 0.0;
    new_sphere2->transparency = 1.0;
    new_sphere2->reflection = 0.5;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere2);

    // Sphere 3
    struct s_spheres *new_sphere3 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere3->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere3->center->x = 5.0;
    new_sphere3->center->y = -1.0;
    new_sphere3->center->z = -15.0;
    new_sphere3->radius = 2.0;
    new_sphere3->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere3->surfaceColor->x = 0.90;
    new_sphere3->surfaceColor->y = 0.76;
    new_sphere3->surfaceColor->z = 0.46;
    new_sphere3->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere3->emissionColor->x = 0.0;
    new_sphere3->emissionColor->y = 0.0;
    new_sphere3->emissionColor->z = 0.0;
    new_sphere3->transparency = 1.0;
    new_sphere3->reflection = 0.0;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere3);

    // Sphere 4
    struct s_spheres *new_sphere4 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere4->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere4->center->x = 5.0;
    new_sphere4->center->y = 0.0;
    new_sphere4->center->z = -25.0;
    new_sphere4->radius = 3.0;
    new_sphere4->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere4->surfaceColor->x = 0.65;
    new_sphere4->surfaceColor->y = 0.77;
    new_sphere4->surfaceColor->z = 0.97;
    new_sphere4->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere4->emissionColor->x = 0.0;
    new_sphere4->emissionColor->y = 0.0;
    new_sphere4->emissionColor->z = 0.0;
    new_sphere4->transparency = 1.0;
    new_sphere4->reflection = 0.0;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere4);

    // Sphere 5
    struct s_spheres *new_sphere5 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere5->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere5->center->x = -5.5;
    new_sphere5->center->y = 0.0;
    new_sphere5->center->z = -15.0;
    new_sphere5->radius = 3.0;
    new_sphere5->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere5->surfaceColor->x = 0.90;
    new_sphere5->surfaceColor->y = 0.90;
    new_sphere5->surfaceColor->z = 0.90;
    new_sphere5->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere5->emissionColor->x = 0.0;
    new_sphere5->emissionColor->y = 0.0;
    new_sphere5->emissionColor->z = 0.0;
    new_sphere5->transparency = 1.0;
    new_sphere5->reflection = 0.0;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere5);

    // Sphere 6 (light)
    struct s_spheres *new_sphere6 = (struct s_spheres *)malloc(sizeof(struct s_spheres));
    new_sphere6->center = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere6->center->x = 0.0;
    new_sphere6->center->y = 20.0;
    new_sphere6->center->z = -30.0;
    new_sphere6->radius = 3.0;
    new_sphere6->surfaceColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere6->surfaceColor->x = 0.0;
    new_sphere6->surfaceColor->y = 0.0;
    new_sphere6->surfaceColor->z = 0.0;
    new_sphere6->emissionColor = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    new_sphere6->emissionColor->x = 3.0;
    new_sphere6->emissionColor->y = 3.0;
    new_sphere6->emissionColor->z = 3.0;
    new_sphere6->transparency = 0.0;
    new_sphere6->reflection = 0.0;
    sphere_struct_vector = sphere_push_back(sphere_struct_vector, new_sphere6);

    // Print all spheres
    print_sphere_struct(sphere_struct_vector);

    return sphere_struct_vector;
}

// Function to free memory allocated for the sphere vector
int clean_sphere_vector(struct s_spheres *sphere_struct_vector)
{
    // Don't forget to free memory when you're done
    for (int i = 0; i < numSpheres; i++)
    {
        free(sphere_struct_vector[i].center);
        free(sphere_struct_vector[i].surfaceColor);
        free(sphere_struct_vector[i].emissionColor);
    }
    free(sphere_struct_vector);
    return 0; // Return 0 to indicate success
}