#include "../includes/Data.h"
/*
void raytraceSphere()
{
    float height = 768;  // Window height
    float width = 1366;  // Window width

    struct s_ray camera; //camera position origin
    camera.origin->x = 0;
    camera.origin->y = 0;
    camera.origin->z = 0;

    camera.direction->x = 0;
    camera.direction->y = 1;
    camera.direction->z = 0;

    struct s_ray light; //light source origin
    light.origin->x = 1;
    light.origin->y = 1;
    light.origin->z = 1;

    light.direction->x = 0;
    light.direction->y = 1;
    light.direction->z = 0;
}
*/

// Plot a horizontal line from (x1, y) to (x2, y)
void plotHorizontalLine(int x1, int x2, int y, t_data *img) {
    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    for (int x = x1; x <= x2; x++) {
        my_mlx_pixel_put(img, x, y, GREEN);
    }
}

// Midpoint Circle Algorithm to draw a filled circle
void drawFilledCircle(int xc, int yc, int r, t_data *img) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r; // Initial decision parameter

    while (x <= y) {
        // Plot horizontal lines for the current y position
        plotHorizontalLine(xc - x, xc + x, yc + y, img);
        plotHorizontalLine(xc - x, xc + x, yc - y, img);
        plotHorizontalLine(xc - y, xc + y, yc + x, img);
        plotHorizontalLine(xc - y, xc + y, yc - x, img);

        // Mirror lines for the lower part of the circle
        plotHorizontalLine(xc - x, xc + x, yc + y, img);
        plotHorizontalLine(xc - x, xc + x, yc - y, img);
        plotHorizontalLine(xc - y, xc + y, yc + x, img);
        plotHorizontalLine(xc - y, xc + y, yc - x, img);

        // Update decision parameter and coordinates
        x++;
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}


void drawSphere(t_data *img) {
    // Allocate memory for the sphere structure
    struct s_sphere *test_circle = (struct s_sphere *)malloc(sizeof(struct s_sphere));
    if (!test_circle) {
        fprintf(stderr, "Memory allocation failed for test_circle\n");
        return;
    }

    // Allocate memory for the sphere origin
    test_circle->origin = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    if (!test_circle->origin) {
        fprintf(stderr, "Memory allocation failed for test_circle->origin\n");
        free(test_circle);  // Clean up previously allocated memory
        return;
    }

    // Initialize sphere parameters
    test_circle->origin->x = 100;
    test_circle->origin->y = 100;
    test_circle->origin->z = 0;
    test_circle->radius = 50.f;

    printf("success test_circle data set up\n");

    // Draw the filled circle
    drawFilledCircle(test_circle->origin->x, test_circle->origin->y, test_circle->radius, img);

    // Free allocated memory
    free(test_circle->origin);
    free(test_circle);
}
