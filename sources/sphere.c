#include "../includes/Data.h"
#include "../includes/Math.h"



float find_smaller_positive_float(float a, float b) {
    // Check both floats and find the smaller one that is greater than 0
    if (a > 0 && b > 0) {
        return (a < b) ? a : b;
    } else if (a > 0) {
        return a;
    } else if (b > 0) {
        return b;
    } else {
        return 0; // Return 0 if neither float is positive
    }
}

// Convert RGBA to 32-bit hexadecimal color format
uint32_t rgbaToHex(struct s_vec3 color) {
    // Clamp the color values between 0 and 1 and then scale to 0-255
    uint8_t r = (uint8_t)(color.x * 255);
    uint8_t g = (uint8_t)(color.y * 255);
    uint8_t b = (uint8_t)(color.z * 255);
    uint8_t a = (uint8_t)(255 * 255);

    // Combine the components into a single 32-bit hexadecimal color
    uint32_t hexColor = (a << 24) | (r << 16) | (g << 8) | b;
    return hexColor;
}

void renderScene(t_data *img) {

    // Initialize camera and light
    struct s_ray *cameraObj = (struct s_ray *)malloc(sizeof(struct s_ray));
    struct s_ray *light = (struct s_ray *)malloc(sizeof(struct s_ray));
    if (!cameraObj || !light) {
        fprintf(stderr, "Memory allocation failed for cameraObj or light\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for `origin` and `direction`
    cameraObj->origin = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    cameraObj->direction = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    light->origin = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    if (!cameraObj->origin || !cameraObj->direction || !light->origin) {
        fprintf(stderr, "Memory allocation failed for cameraObj->origin, cameraObj->direction, or light->origin\n");
        free(cameraObj->origin);
        free(cameraObj->direction);
        free(cameraObj);
        free(light->origin);
        free(light);
        exit(EXIT_FAILURE);
    }

    // Camera setup
    cameraObj->origin->x = width / 2;
    cameraObj->origin->y = height / 2;
    cameraObj->origin->z = 0;
    cameraObj->direction->x = 1;
    cameraObj->direction->y = 0;
    cameraObj->direction->z = -1;

    // Light setup
    light->origin->x = -200;
    light->origin->y = 200;
    light->origin->z = -100;

    float fov = 90.0f;

    // Loop through each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Generate a ray for the current pixel
            struct s_ray *ray = (struct s_ray *)malloc(sizeof(struct s_ray));
            if (!ray) {
                fprintf(stderr, "Memory allocation failed for ray\n");
                exit(EXIT_FAILURE);
            }

            // Allocate memory for `direction` of the new ray
            ray->direction = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
            if (!ray->direction) {
                fprintf(stderr, "Memory allocation failed for ray->direction\n");
                free(ray);
                exit(EXIT_FAILURE);
            }

            ray->origin = cameraObj->origin;
            struct s_vec3 resultingDir = generateRayDirection(x, y, width, height, fov);
            ray->direction->x = resultingDir.x;
            ray->direction->y = resultingDir.y;
            ray->direction->z = resultingDir.z;

            // Call raytraceSphere for the current pixel
            struct s_vec3 pixelColor = raytraceSphere(*ray, *light->origin);

            // Set the pixel color
            uint32_t uIntPixelColor = rgbaToHex(pixelColor);
            my_mlx_pixel_put(img, x, y, uIntPixelColor);

            // Free memory allocated for the ray
            free(ray->direction);
            free(ray);
        }
    }

    // Free memory allocated for camera and light
    free(cameraObj->origin);
    free(cameraObj->direction);
    free(cameraObj);
    free(light->origin);
    free(light);
}


struct s_vec3 generateRayDirection(int px, int py, float width, float height, float fov)
{
    //find normalized device coordinates
    float normx = (px + 0.5)/width;
    float normy = (py + 0.5)/height;

    //map to range [-1, 1]
    float NDCx = 2 * normx - 1;
    float NDCy = 1 - 2 * normy;

    //computing scale
    float scale = tanf((fov/2) * (PI/180));

    //find ray direction
    float ray_directionx = NDCx * scale;
    float ray_directiony = NDCy * scale;
    float ray_directionz = -1;

    //length of ray direction
    float length = powf(pow(ray_directionx, 2) + pow(ray_directiony, 2) +pow(ray_directionz, 2) ,0.5);
    
    //normalise ray direction;
    ray_directionx = ray_directionx / length;
    ray_directiony = ray_directiony / length;
    ray_directionz = ray_directionz / length;

    return createVec3(ray_directionx, ray_directiony, ray_directionz);
}


struct s_vec3 raytraceSphere(struct s_ray ray, struct s_vec3 lightOrigin) {
    // Sphere setup (as before)
    struct s_sphere *sphereObj = (struct s_sphere*)malloc(sizeof(struct s_sphere));
    sphereObj->origin = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    sphereObj->origin->x = width / 2;
    sphereObj->origin->y = height / 2;
    sphereObj->origin->z = 0;
    sphereObj->radius = 10.f;

    float t_value = intersectRaySphere(ray, *sphereObj);
    if (t_value < 0) {
        // No intersection, return background color
        struct s_vec3 black = {0.0, 0.0, 0.0};
        return black;  // Black or other background color
    }

    struct s_vec3 intersectPoint = rayAt(ray, t_value);

    // Compute normal and lighting (as before)
    struct s_vec3 pointMinusOrigin = vec3_sub(intersectPoint, *(sphereObj->origin));
    struct s_vec3 normalAtIntersectPoint = vec3_normalize(pointMinusOrigin);
    
    struct s_vec3 lightDir = vec3_normalize(vec3_sub(lightOrigin, intersectPoint));
    
    // Ambient, diffuse, and specular calculations (as before)    
    struct s_vec3 Iambient = scalarMult(createVec3(0.5f, 0.3f, 0.3f), 0.5);
    struct s_vec3 Idiffuse = scalarMult(scalarMult(createVec3(1.0f, 1.0f, 1.0f), 0.5), maxft(dot(normalAtIntersectPoint, lightDir), 0));
    
    struct s_vec3 R = vec3_sub(scalarMult(normalAtIntersectPoint, 2 * dot(normalAtIntersectPoint, lightDir)), lightDir);
    struct s_vec3 viewDirection = vec3_normalize(vec3_sub(*ray.origin, intersectPoint));
    struct s_vec3 Ispecular = scalarMult(scalarMult(createVec3(1.0f, 1.0f, 1.0f), 0.5), pow(maxft(dot(R, viewDirection), 0), 150));

    struct s_vec3 I = vec3_add(vec3_add(Iambient, Idiffuse), Ispecular);
    return I;
}