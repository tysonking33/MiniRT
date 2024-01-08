#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>


int numSpheres;
int imageWidth;
int imageHeight;

struct s_vec3
{
    float x;
    float y;
    float z;
} t_vec3;

struct s_spheres
{
    struct s_vec3 *center;
    float radius, radius2;
    struct s_vec3 *surfaceColor;
    struct s_vec3 *emissionColor;
    float transparency, reflection;
} t_spheres;

struct s_rays
{
    struct s_vec3 *origin;
    struct s_vec3 *direction;
} t_rays;

struct s_camera {
    struct s_vec3 eyePosition;
    struct s_vec3 lookAt;
    struct s_vec3 upVector;
    float fov;  // Field of view in degrees
} t_camera;


struct s_object {
    struct s_spheres *sphere;
} t_object;

/* start main.c */
int main(int argc, char **argv);
/* end main.c */

/* start sphere_init_n_clean.c */
struct s_spheres *sphere_push_back(struct s_spheres *sphere_struct_vector, struct s_spheres *new_sphere);
void print_sphere_struct(struct s_spheres *sphere_struct_vector);
struct s_spheres *insert_spheres(struct s_spheres *sphere_struct_vector);
int clean_sphere_vector(struct s_spheres *sphere_struct_vector);
/* end sphere_init_n_clean.c */


/* start vector_math.c */
struct s_vec3 *crossProduct(struct s_vec3 *a, struct s_vec3 *b);
struct s_vec3 *normalize(struct s_vec3 *v);
struct s_vec3 *subtract(struct s_vec3 *a, struct s_vec3 *b);
struct s_vec3 *addScalar(struct s_vec3 *v, float scalar);
struct s_vec3 *multiplyScalar(struct s_vec3 *v, float scalar);
float dotProduct(struct s_vec3 *a, struct s_vec3 *b);
struct s_vec3 *add(struct s_vec3 *a, struct s_vec3 *b);
float distance(struct s_vec3 *a, struct s_vec3 *b);
/* end vector_math.c */

/* start raytracing_algo.c */
void computePrimRay(int i, int j, struct s_rays *primRay, struct s_camera *camera);
void start_raytracing(struct s_object *object_vector, struct s_camera *camera);
/* end raytracing_algo.c */


#endif