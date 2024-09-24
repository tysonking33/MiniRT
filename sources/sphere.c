#include "../includes/Data.h"
#include "../includes/Math.h"

// Convert RGBA to 32-bit hexadecimal color format
uint32_t rgbaToHex(t_vec3 color)
{
    // Clamp the color values between 0 and 1 and then scale to 0-255
    uint8_t r = (uint8_t)(color.x * 255);
    uint8_t g = (uint8_t)(color.y * 255);
    uint8_t b = (uint8_t)(color.z * 255);
    uint8_t a = 255; // Alpha should be just 255, not 255 * 255

    // Combine the components into a single 32-bit hexadecimal color
    uint32_t hexColor = (a << 24) | (r << 16) | (g << 8) | b;
    return hexColor;
}

t_vec3 computeSphereObjNormal(t_vec3 intersectionPoint, struct s_sphere sphere)
{
    t_vec3 sphereNormal = vec3_sub(intersectionPoint, *(sphere.origin));
    return vec3_normalize(sphereNormal); // Normalize this vector to get the surface normal
}

// Render the scene by checking ray-sphere intersections
void renderScene(t_data *img, t_scene *scene)
{
    int width = 1366;
    int height = 768;
    float aspect_ratio = (float)width / (float)height;
    t_ray ray;
    ray.origin = scene->camera->origin;
    t_vec3 direction;  // Use a regular vector for direction
    float t;

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
            *ray.direction = direction;  // Assign the direction vector to ray

            // Check for sphere intersection
            if (raySphereIntersect(&ray, scene->sphere, &t))
            {
                // If the ray hits the sphere, compute the color using ray tracing
                t_vec3 color = raytraceSphere(ray, *scene);
                uint32_t hexColor = rgbaToHex(color);
                my_mlx_pixel_put(img, x, y, hexColor);
            }
            else
            {
                // If no hit, set background color (black)
                my_mlx_pixel_put(img, x, y, 0x000000);
            }

            free(ray.direction);  // Clean up dynamically allocated memory
        }
    }
}



t_vec3 generateRayDirection(int x, int y, t_scene *scene) {
    // Compute normalized screen space coordinates
    float aspectRatio = scene->width / scene->height;
    float px = (2 * ((x + 0.5) / scene->width) - 1) * aspectRatio * tan(scene->fov / 2);
    float py = (1 - 2 * ((y + 0.5) / scene->height)) * tan(scene->fov / 2);
    
    t_vec3 rayDirection = {px, py, -1.0f};  // Assuming the camera looks down the negative Z-axis
    rayDirection = vec3_normalize(rayDirection);
    return rayDirection;
}

t_vec3 raytraceSphere(struct s_ray ray, t_scene sceneObj)
{
    t_vec3 lightOrigin = *sceneObj.light->origin;
    t_sphere sphereObj = *sceneObj.sphere;

    // Find the intersection of the ray with the sphere
    float t_value = intersectRaySphere(ray, sphereObj);
    if (t_value < 0)
    {
        // No intersection, return background color
        t_vec3 sky_blue = {0.529, 0.808, 0.922};
        return sky_blue; // Black or other background color
    }

    // Calculate the intersection point on the sphere
    t_vec3 intersectPoint = rayAt(ray, t_value);

    // **Call computeSphereObjNormal here**
    t_vec3 normalAtIntersectPoint = computeSphereObjNormal(intersectPoint, sphereObj);

    // Compute lighting (as before)
    t_vec3 lightDir = vec3_normalize(vec3_sub(lightOrigin, intersectPoint));

    // Ambient, diffuse, and specular lighting calculations (as before)
    t_vec3 Iambient = scalarMult(createVec3(0.5f, 0.3f, 0.3f), 0.5);
    t_vec3 Idiffuse = scalarMult(scalarMult(createVec3(1.0f, 1.0f, 1.0f), 0.5), maxft(dot(normalAtIntersectPoint, lightDir), 0));

    t_vec3 R = vec3_sub(scalarMult(normalAtIntersectPoint, 2 * dot(normalAtIntersectPoint, lightDir)), lightDir);
    t_vec3 viewDirection = vec3_normalize(vec3_sub(*ray.origin, intersectPoint));
    t_vec3 Ispecular = scalarMult(scalarMult(createVec3(1.0f, 1.0f, 1.0f), 0.5), pow(maxft(dot(R, viewDirection), 0), 150));

    // Combine the lighting components
    t_vec3 I = vec3_add(vec3_add(Iambient, Idiffuse), Ispecular);


    //free(sphereObj.origin);

    return I;
}


// Computes the normal of the sphere at a given intersection point
t_vec3 computeSphereNormal(t_vec3 intersection, t_sphere sphere)
{
    t_vec3 normal = vec3_sub(intersection, *sphere.origin);
    return vec3_normalize(normal);
}

// Ray-sphere intersection function
int raySphereIntersect(t_ray *ray, t_sphere *sphere, float *t) {
    t_vec3 oc = vec3_sub(*ray->origin, *sphere->origin);
    float a = dot(*ray->direction, *ray->direction);
    float b = 2.0 * dot(oc, *ray->direction);
    float c = dot(oc, oc) - sphere->radius * sphere->radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0; // No intersection
    } else {
        *t = (-b - sqrt(discriminant)) / (2.0 * a); // Return the closest intersection
        return 1; // Intersection occurs
    }
}

