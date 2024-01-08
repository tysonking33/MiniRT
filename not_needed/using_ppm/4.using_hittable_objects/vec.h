#ifndef VEC_H
#define VEC_H


#define WIDTH 800
#define HEIGHT 800

#include <stdlib.h>
#include <stdio.h>
#include <math.h>




// start Struct definition for s_vec3 in vec_utils.c
typedef struct s_vec3 {
    float x, y, z;
} t_vec3;

// Constructors
struct s_vec3 *make_vec3(float x, float y, float z);

// Accessors
float get_vec3_x(struct s_vec3 *v);
float get_vec3_y(struct s_vec3 *v);
float get_vec3_z(struct s_vec3 *v);

// Unary operators
struct s_vec3 *vec3_neg(struct s_vec3 *v);

// Indexing
float vec3_at(struct s_vec3 *v, int i);

// Compound assignment operators
struct s_vec3 * vec3_mul_float(struct s_vec3 * v, float t);
struct s_vec3 *vec3_div(struct s_vec3 *v, float t);
struct s_vec3 *vec3_add_float(struct s_vec3 * v, float t);

// Length-related functions
float vec3_length(struct s_vec3 *v);
float vec3_length_squared(struct s_vec3 *v);

// Vector utility functions
void vec3_print(struct s_vec3 *v);
struct s_vec3 *vec3_add(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_sub(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 * vec3_mul_vec(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_scale(float t, struct s_vec3 *v);
float vec3_dot(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_cross(struct s_vec3 *u, struct s_vec3 *v);
struct s_vec3 *vec3_unit_vector(struct s_vec3 *v);

// Free memory for vec3
void free_vec3(struct s_vec3 *v);





// end struct s_vec3 and related functions

//start Struct definition for s_ray in ray_util.c

typedef struct s_ray{
    struct s_vec3 *origin;
    struct s_vec3 *direction;
}   t_ray;

struct s_ray *make_s_ray(struct s_vec3 *origin, struct s_vec3 *direction);

struct s_vec3 *get_origin(struct s_ray *ray);
struct s_vec3 *get_direction(struct s_ray *ray);
struct s_vec3 *at(struct s_ray *ray, float t);
void free_s_ray(struct s_ray *r);
// end struct s_ray and related functions


/* start Struct definition for s_sphere in sphere.c */

typedef struct s_hit_record{
    struct s_vec3 *point_p;
    struct s_vec3 *normal;
    float t;
    float front_face_bool;        //true if value is more than 0
}   t_hit_record;


typedef struct s_sphere{
    struct s_vec3 *center;
    float radius;
}   t_sphere;

struct s_sphere *make_s_sphere(struct s_vec3 *center, float radius);
struct s_vec3 *get_sphere_center(struct s_sphere *src_sphere);
float get_sphere_radius(struct s_sphere *src_sphere);
float sphere_hit(struct s_sphere *sphere, struct s_ray * r, float ray_tmin, float ray_tmax, struct s_hit_record * record);
void set_face_normal(struct s_hit_record *hit_record, struct s_ray *r, struct s_vec3 *outward_normal);   //make the normal always point outwards fromt he surface
void draw_sphere();

/* end struct s_ray and related functions */



/* start maths in math_constants.c */
# define infinity 2147483647
# define pi 3.1415926535897932385
float degrees_to_radians(float degrees);
/* end math_constants.c */



/*in using_vect.c */
void write_color(FILE *file, struct s_vec3 * color);
void draw_gradient();
int main();

/* in draw_circle.c */
float hit_sphere(struct s_vec3 *center, float radius, struct s_ray *r);
struct s_vec3 *ray_color(struct s_ray *r);
void draw_circle();

#endif // VEC_H