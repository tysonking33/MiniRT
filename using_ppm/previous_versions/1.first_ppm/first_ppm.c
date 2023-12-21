#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vec3{
    float x, y, z;
} t_vec3;

typedef struct {
    struct s_vec3 *origin;
    struct s_vec3 *direction;
} t_ray;

typedef struct s_sphere{
    struct s_vec3 *center;
    float radius;
} t_sphere;

float dot(struct s_vec3 *v1, struct s_vec3 *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}



void write_color(FILE *file, struct s_vec3 * color) {
    fprintf(file, "%d %d %d\n",
            (int)(255.999 * color->x),
            (int)(255.999 * color->y),
            (int)(255.999 * color->z));
}



int main() {
    int image_width = 256;
    int image_height = 256;
    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);


    
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            float r = (float)(i) / (image_width-1);
            float g = (float)(j) / (image_height-1);
            float b = 0;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            fprintf(image, "%d %d %d\n", ir, ig, ib);
        }
    }

    fclose(image);
    return 0;
}