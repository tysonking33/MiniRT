#include "vec.h"

void write_color(FILE *file, struct s_vec3 *color) {
    fprintf(file, "%d %d %d\n",
            (int)(255.999 * color->x),
            (int)(255.999 * color->y),
            (int)(255.999 * color->z));
    //free_vec3(color);  // Free the memory allocated for color
}

void draw_gradient()
{
    int image_width = 256;
    int image_height = 256;
    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        printf("\rScanlines remaining: %d\n", image_height - j);
        for (int i = 0; i < image_width; ++i) {
            float r = (float)(i) / (image_width - 1);
            float g = (float)(j) / (image_height - 1);
            float b = 0;

            struct s_vec3 *color = make_vec3(r, g, b);

            write_color(image, color);
        }
    }
    printf("\rDone.                 \n");

    fclose(image);
}



int main() {
    draw_circle();
    return 0;
}
