#include "minirt.h"

void computePrimRay(int i, int j, struct s_rays *primRay, struct s_camera *camera)
{
    float aspectRatio = (float)imageWidth / (float)imageHeight;
    float fov = 45.0;
    float angle = tan(M_PI * 0.5 * fov / 180.0);

    // Calculate camera right and up vectors
    struct s_vec3 *cameraRight = crossProduct(normalize(&camera->upVector), subtract(&camera->lookAt, &camera->eyePosition));
    struct s_vec3 *cameraUp = crossProduct(cameraRight, subtract(&camera->lookAt, &camera->eyePosition));

    // Calculate ray direction in screen space
    float x = (2.0 * (i + 0.5) / (float)imageWidth - 1.0) * aspectRatio * angle;
    float y = (1.0 - 2.0 * (j + 0.5) / (float)imageHeight) * angle;

    // Calculate primary ray direction
    struct s_vec3 *rayDirection = add(add(multiplyScalar(cameraRight, x), multiplyScalar(cameraUp, y)), &camera->lookAt);
    rayDirection = normalize(rayDirection);

    // Set the origin and direction of the primary ray
    primRay->origin = &camera->eyePosition;
    primRay->direction = rayDirection;
}

int intersect(struct s_spheres *current_sphere, struct s_rays *raydir, float *t0, float *t1)
{
    struct s_vec3 *l = subtract(current_sphere->center, raydir->origin);
    float tca = dotProduct(raydir->direction, l);
    if (tca < 0)
        return -1;
    float d2 = dotProduct(l, l) - tca * tca;
    if (d2 > current_sphere->radius2)
        return -1;
    float thc = sqrt(current_sphere->radius2 - d2);
    *t0 = tca - thc;
    *t1 = tca + thc;

    return 1;
}

void start_raytracing(struct s_object *object_vector, struct s_camera *camera)
{
    int current_height = 0;
    struct s_vec3 *lightPosition = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
    lightPosition->x = 5.0;
    lightPosition->y = 10.0;
    lightPosition->z = 8.0;
    while (current_height < imageHeight)
    {
        int current_width = 0;
        while (current_width < imageWidth)
        {
            struct s_rays *primRay = (struct s_rays *)malloc(sizeof(struct s_rays));
            computePrimRay(current_height, current_width, primRay, camera);

            struct s_vec3 *pHit = (struct s_vec3 *)malloc(sizeof(struct s_vec3));
            struct s_vec3 *nHit = (struct s_vec3 *)malloc(sizeof(struct s_vec3));

            float minDistance = INFINITY;
            struct s_spheres *sphere_vector = object_vector->sphere;

            struct s_spheres *current_sphere = (struct s_spheres *)malloc(sizeof(struct s_spheres));
            int k = 0;

            while (k < numSpheres)
            {
                if (intersect(&sphere_vector[k], primRay, pHit, nHit))
                {
                    float distance = distance(&camera->eyePosition, pHit);
                    if (distance < minDistance)
                    {
                        current_sphere = &sphere_vector[k];
                        minDistance = distance;  // update min distance
                    }
                }

                ++k;
            }

            if (current_sphere != NULL)
            {
                // compute illumination
                struct s_rays *shadowRay = (struct s_rays *)malloc(sizeof(struct s_rays));
                shadowRay->direction = subtract(&lightPosition, pHit); // Assuming lightPosition is a struct s_vec3

                int isInShadow = -1;

                for (int k = 0; k < numSpheres; ++k)
                {
                    if (intersect(&sphere_vector[k], shadowRay, NULL, NULL))
                    {
                        isInShadow = 1;
                        break;
                    }
                }

                if (!isInShadow)
                    pixels[current_width][current_height] = multiplyScalar(&current_sphere->surfaceColor, light.brightness); // Assuming pixels is a 2D array
                else
                    pixels[current_width][current_height] = 0;
            }
            ++current_width;
        }
        ++current_height;
    }
}
