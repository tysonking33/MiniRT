#include "../includes/Data.h"
#include "../includes/Math.h"

void renderScenePlane(t_data *img, t_scene *scene)
{
    int width = 1366;
    int height = 768;
    float aspect_ratio = (float)width / (float)height;
    t_ray ray;
    ray.origin = scene->camera->origin;
    t_ray reflected_ray;
    reflected_ray.origin = scene->camera->origin;
    t_vec3 direction; // Use a regular vector for direction
    float t = 0.0f;
    float closest_t = 0.0f;
    t_plane *closest_plane;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Calculate the ray direction for each pixel

            // Normalize coordinates to NDC (Normalized Device Coordinates)
            float u = (2.0f * ((float)x + 0.5f) / (float)width - 1.0f) * aspect_ratio;
            float v = 1.0f - 2.0f * ((float)y + 0.5f) / (float)height;

            // Adjust for FOV (assuming vertical FOV, adjust the ray's angle)
            float fov_adjustment = tan(scene->fov * (PI / 180.0f) / 2.0f);
            direction = vec3_normalize(createVec3(u * fov_adjustment, v * fov_adjustment, -1.0f));

            ray.direction = malloc(sizeof(t_vec3));
            *ray.direction = direction; // Assign the direction vector to ray

            closest_plane = NULL;
            closest_t = FLT_MAX;
            t = FLT_MAX;

            // Check for sphere intersection
            t_plane *current_plane = &(scene->plane[0]);

            rayPlaneIntersect(&ray, current_plane, &t);
            if (t < closest_t)
            {
                closest_t = t;
                closest_plane = current_plane;
            }

            t_vec3 intersectPoint = rayAt(ray, closest_t);

            (void)reflected_ray;

            /*---------------------reflection start-------------------------------------*/
            /*
                *reflected_ray.origin = intersectPoint;
                reflected_ray.direction = (t_vec3 *)malloc(sizeof(t_vec3));
                *reflected_ray.direction = vec3_sub(*ray.direction, scalarMult(*current_plane->normal, 2 * dot(*ray.direction, *current_plane->normal)));
            */
            /*---------------------reflection end-------------------------------------*/

            if (checkIfBounded(&ray, closest_plane, closest_t) && closest_plane != NULL)
            {
                // If the ray hits the sphere, compute the color using ray tracing
                t_vec3 color = raytracePlane(ray, *closest_plane, scene->light, *scene, intersectPoint);

                uint32_t hexColor = rgbaToHex(color);
                my_mlx_pixel_put(img, x, y, hexColor);
            }
            else
            {
                // If no hit, set background color (RED)
                my_mlx_pixel_put(img, x, y, BLACK);
            }

            free(ray.direction); // Clean up dynamically allocated memory
        }
    }
}

int rayPlaneIntersect(t_ray *ray, t_plane *plane, float *t)
{
    t_vec3 *n = plane->normal;
    t_vec3 *Porigin = plane->origin;
    t_vec3 *Rdirection = ray->direction;
    t_vec3 *Rorigin = ray->origin;

    float RD_Dot_n = dot(*Rdirection, *n);
    if (RD_Dot_n == 0)
    {
        // ray parallel to plplane, no intersection
        return 0;
    }
    else
    {
        *t = dot(vec3_sub(*Porigin, *Rorigin), *n) / RD_Dot_n;
        return 1;
    }
}

int checkIfBounded(t_ray *ray, t_plane *plane, float t)
{
    t_vec3 *P = (t_vec3 *)malloc(sizeof(t_vec3)); // intersection point
    *P = rayAt(*ray, t);

    t_vec3 *A = plane->P1;
    t_vec3 *B = plane->P2;
    t_vec3 *C = plane->P3;
    t_vec3 *D = plane->P4;

    // using Barycentric Coordinates
    // triangle1 = A,B,C
    t_vec3 v00 = vec3_sub(*B, *A);
    t_vec3 v01 = vec3_sub(*C, *A);
    t_vec3 v02 = vec3_sub(*P, *A);

    float d00 = dot(v00, v00);
    float d01 = dot(v00, v01);
    float d11 = dot(v01, v01);
    float d20 = dot(v02, v00);
    float d21 = dot(v02, v01);

    float denom = d00 * d11 - d01 * d01;

    // find barycentric coordinates
    float u = (d11 * d20 - d01 * d21) / denom;
    float v = (d00 * d21 - d01 * d20) / denom;
    //float w = 1 - u - v;

    if ((0 <= u && u <= 1) && (0 <= v && v <= 1) && (u + v <= 1))
    {
        // point is in triangle 1
        return 1;
    }

    // triangle2 = A,C,D
    t_vec3 v10 = vec3_sub(*C, *D);
    t_vec3 v11 = vec3_sub(*B, *D);
    t_vec3 v12 = vec3_sub(*P, *D);

    d00 = dot(v10, v10);
    d01 = dot(v10, v11);
    d11 = dot(v11, v11);
    d20 = dot(v12, v10);
    d21 = dot(v12, v11);

    denom = d00 * d11 - d01 * d01;

    // find barycentric coordinates
    u = (d11 * d20 - d01 * d21) / denom;
    v = (d00 * d21 - d01 * d20) / denom;
    //w = 1 - u - v;

    if ((0 <= u && u <= 1) && (0 <= v && v <= 1) && (u + v <= 1))
    {
        // point is in triangle 2
        return 1;
    }

    // not in the plane
    return 0;
}

t_vec3 raytracePlane(t_ray ray, t_plane plane, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint)
{
    (void)ray;
    (void)lightObj;
        
    // Define colors
    t_vec3 lightColor = {1.0, 1.0, 1.0};  // Assuming white light
    t_vec3 objectColor = {1.0, 0.4, 0.2}; // Example object color (red-ish)

    // Ambient lighting
    float ka = 0.5;                          // Ambient reflection coefficient (between 0 and 1)
    t_vec3 Ia = scalarMult(lightColor, 0.5); // Ambient light intensity from the environment
    t_vec3 Iambient = scalarMult(Ia, ka);    // Ambient lighting color

    // Diffuse lighting
    float kd = 1; // Diffuse reflection coefficient
    t_vec3 lightPos_minus_intersectPos = vec3_sub(*sceneObj.light->origin, intersectionPoint);
    t_vec3 L = scalarMult(lightPos_minus_intersectPos, 1 / vec3_magnitude(lightPos_minus_intersectPos));
    t_vec3 N = *plane.normal;

    float dotLN = dot(L, N);
    if (dotLN < 0.0f)
    {
        dotLN = 0.0f; // Ensure the dot product is non-negative
    }

    t_vec3 Id = scalarMult(lightColor, 0.5);      // Intensity of the light source
    t_vec3 Idiffuse = scalarMult(Id, kd * dotLN); // Diffuse lighting color

    // Specular lighting (Phong reflection model)
    float ks = 0.5;                                   // Specular reflection coefficient
    t_vec3 R = vec3_sub(scalarMult(N, 2 * dotLN), L); // Reflected light direction
    t_vec3 C = *sceneObj.camera->origin;
    t_vec3 V = vec3_sub(C, intersectionPoint);
    normalise(&V); // Normalize the view direction

    float n = 50.0f; // Shininess exponent (size of the specular highlight)
    float dotRV = dot(R, V);
    if (dotRV < 0.0f)
    {
        dotRV = 0.0f; // Ensure the dot product is non-negative
    }

    t_vec3 Is = scalarMult(lightColor, 0.5);               // Intensity of the light source for specular
    t_vec3 Ispecular = scalarMult(Is, ks * pow(dotRV, n)); // Specular lighting color

    // Combine the lighting components
    t_vec3 finalColor = vec3_add(vec3_add(Iambient, Idiffuse), Ispecular);

    // Apply the object's color
    finalColor = vec3_mult(finalColor, objectColor); // Element-wise multiplication

    return finalColor; // Return the resulting RGB color vector
}

// Function to perform element-wise multiplication of two t_vec3 vectors
t_vec3 vec3_mult(t_vec3 v1, t_vec3 v2)
{
    t_vec3 result;
    result.x = v1.x * v2.x;
    result.y = v1.y * v2.y;
    result.z = v1.z * v2.z;
    return result;
}

t_vec3 calculateShadow(t_ray ray, t_plane plane, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint)
{
    (void)ray;
    (void)plane;
    (void)sceneObj;
    (void)intersectionPoint;
    (void)lightObj;
    // Define colors
    t_vec3 lightColor = {1.0, 1.0, 1.0};  // Assuming white light
    t_vec3 objectColor = {0.8, 0.4, 0.2}; // Example object color (red-ish)

    // Ambient lighting
    float ka = 0.5;                          // Ambient reflection coefficient (between 0 and 1)
    t_vec3 Ia = scalarMult(lightColor, 0.5); // Ambient light intensity from the environment
    t_vec3 Iambient = scalarMult(Ia, ka);    // Ambient lighting color

    t_vec3 finalColor = vec3_mult(Iambient, objectColor); // Element-wise multiplication

    return finalColor;
}