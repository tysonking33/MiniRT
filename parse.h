#ifndef PARSE_H
#define PARSE_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct s_sphere_init {
    float *sphere_xyz;
    float sphere_diameter;
    float *sphere_rgb;
}               t_sphere_init;

typedef struct s_plane_init {
    float *plane_xyz;
    float *plane_normalised_vector;
    float *plane_rgb;
}               t_plane_init;

typedef struct s_cylinder_init {
    float *cylinder_xyz;
    float *cylinder_normalised_vector;
    float cylinder_diameter;
    float cylinder_height;
    float *cylinder_rgb;
}               t_cylinder_init;

typedef struct s_init {
    //light
    float ambient_ratio;
    float *ambient_rgb;

    //camera
    float *camera_xyz;
    float *camera_orientation;
    float camera_fov;

    //light
    float *light_xyz;
    float light_ratio;

    //sphere array
    int sphere_count;
    struct s_sphere_init *sphere_array;

    //plane array
    int plane_count;
    struct s_plane_init *plane_array;

    //cylinder array
    int cylinder_count;
    struct s_cylinder_init *cylinder_array;
}               t_init;

/* in ft_split.h */
static int count_words(const char *str, char c);
static char *word_dup(const char *str, int start, int finish);
char **ft_split(char const *s, char c);

/* in parse_scene.c */
int print_values(struct s_init *initial_data_struct);
int parse_line(char *line, struct s_init *inital_data_struct);
float *parse_float_array(char *token, char delimiter);
int read_and_parse_file(char *filename, struct s_init *inital_data_struct);
int first_time_read(char *filename, struct s_init* inital_data_struct);
int main(int argc, char **argv);

#endif
