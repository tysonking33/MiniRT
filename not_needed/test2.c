#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define MAX_COLOR 255

typedef struct {
    unsigned char red, green, blue;
} Color;

void writePPM(const char *filename, Color image[WIDTH][HEIGHT]) {
    FILE *file = fopen(filename, "wb");
    fprintf(file, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            //printf("%d %d %d\n", image[i][j].red, image[i][j].green, image[i][j].blue);
            /*fputc(image[i][j].red, file);
            fputc(image[i][j].green, file);
            fputc(image[i][j].blue, file);*/

            fprintf(file, "%d %d %d\n",
            (int)(255.999 * image[i][j].red),
            (int)(255.999 * image[i][j].green),
            (int)(255.999 * image[i][j].blue));
        }
    }

    fclose(file);
}

void drawRayTracedCircle(Color image[WIDTH][HEIGHT], int lightX, int lightY) {
    // Center of the circle
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;

    // Radius of the circle
    int radius = 200;

    // Number of rays
    int numRays = 360;

    // Draw the circle
    for (int i = 0; i < numRays; i++) {
        double angle = 2.0 * M_PI * i / numRays;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));

        // Check bounds to avoid segmentation faults
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            // Calculate distance from the light source
            double distance = sqrt(pow(x - lightX, 2) + pow(y - lightY, 2));

            // Calculate brightness based on distance
            unsigned char brightness = (unsigned char)(MAX_COLOR - (distance / radius) * MAX_COLOR);

            image[x][y].red = brightness;
            image[x][y].green = brightness;
            image[x][y].blue = brightness;
        }
    }
}

int main() {
    Color image[WIDTH][HEIGHT] = {0}; // Initialize image to black

    int lightX, lightY;

    printf("Enter X coordinate of the light source: ");
    scanf("%d", &lightX);

    printf("Enter Y coordinate of the light source: ");
    scanf("%d", &lightY);

    drawRayTracedCircle(image, lightX, lightY);

    writePPM("output.ppm", image);

    return 0;
}
