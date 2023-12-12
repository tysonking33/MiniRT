#ifndef CURRENT_VALUES_H
#define CURRENT_VALUES_H

#include <math.h>

// Vector structure
typedef struct s_vector3{
    float x, y, z;
} t_vector3;

typedef struct s_vector2{
    float x, y;
} t_vector2;

// Color structure
typedef struct s_color{
    int r, g, b;
} t_color;

// Camera structure
typedef struct s_camera{
    char *identifier;
    struct s_vector3 position;
    struct s_vector3 orientation;
    float fov;  // Field of view in degrees
} t_camera;

// Light structure
typedef struct s_light{
    char *identifier;
    struct s_vector3 position;
    float brightness;
    struct s_color color;
} t_light;

// Sphere structure
typedef struct s_sphere{
    char *identifier;
    struct s_vector3 center;
    float diameter;
    struct s_color color;
} t_sphere;

// Plane structure
typedef struct s_plane{
    char *identifier;
    struct s_vector3 point;
    struct s_vector3 normal;
    struct s_color color;
} t_plane;

// Cylinder structure
typedef struct s_cylinder{
    char *identifier;
    struct s_vector3 center;
    struct s_vector3 axis;
    float diameter;
    float height;
    struct s_color color;
} t_cylinder;

// Ambient light structure
typedef struct s_ambient_light{
    char *identifier;
    float ratio;
    struct s_color color;
} t_ambient_light;

// Scene structure
typedef struct s_scene{
    struct s_camera camera;
    struct s_light light;
    struct s_sphere sphere;
    struct s_plane plane;
    struct s_cylinder cylinder;
    struct s_ambient_light ambientLight;
} t_scene;

#endif
