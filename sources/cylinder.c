#include "../includes/Data.h"
#include "../includes/Math.h"

void renderSceneCylinder(t_data *img, t_scene *scene)
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
    t_cylinder *closest_cylinder;

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

            closest_cylinder = NULL;
            closest_t = FLT_MAX;
            t = FLT_MAX;

            // Check for sphere intersection
            t_cylinder *current_cylinder = &(scene->cylinder[0]);

            rayCylinderIntersect(&ray, current_cylinder, &t);
            if (t < closest_t)
            {
                closest_t = t;
                closest_cylinder = current_cylinder;
            }

            t_vec3 intersectPoint = rayAt(ray, closest_t);

            (void)reflected_ray;

            /*---------------------reflection start-------------------------------------*/
            /*
                *reflected_ray.origin = intersectPoint;
                reflected_ray.direction = (t_vec3 *)malloc(sizeof(t_vec3));
                *reflected_ray.direction = vec3_sub(*ray.direction, scalarMult(*current_cylinder->normal, 2 * dot(*ray.direction, *current_cylinder->normal)));
            */
            /*---------------------reflection end-------------------------------------*/

            if (closest_cylinder != NULL)
            {
                findSurfaceNormal(scene, &intersectPoint, closest_cylinder);
                // If the ray hits the sphere, compute the color using ray tracing
                t_vec3 color = raytraceCylinder(ray, *closest_cylinder, scene->light, *scene, intersectPoint);

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

int rayCylinderIntersect(t_ray *ray, t_cylinder *cylinder, float *t) {
    float radius = cylinder->radius;
    float height = cylinder->height; // Add height here

    t_vec3 O = *ray->origin;
    t_vec3 D = *ray->direction;

    float a = pow(D.x, 2) + pow(D.z, 2);
    float b = 2 * O.x * D.x + 2 * O.z * D.z;
    float c = pow(O.x, 2) + pow(O.z, 2) - pow(radius, 2);

    float discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0) {
        return -1; // No intersection
    }

    float tminus = (-b - sqrt(discriminant)) / (2 * a);
    float tplus = (-b + sqrt(discriminant)) / (2 * a);

    // Check the height for both intersections
    float y_at_tminus = O.y + tminus * D.y; // Calculate the Y-coordinate at tminus
    float y_at_tplus = O.y + tplus * D.y;   // Calculate the Y-coordinate at tplus

    if (tminus > 0 && y_at_tminus >= cylinder->origin->y -height && y_at_tminus <= cylinder->origin->y + height) {
        *t = tminus; // Use closer intersection
        return 1;
    } 
    else if (tplus > 0 && y_at_tplus >= cylinder->origin->y-height && y_at_tplus <= cylinder->origin->y + height) {
        *t = tplus; // Use further intersection
        return 1;
    } 
    else {
        return -1; // Both intersections are either behind the camera or outside cylinder height
    }
}


void findSurfaceNormal(t_scene *sceneObj, t_vec3 *intersectionPoint, t_cylinder *cylinder)
{
    (void)sceneObj;
    t_vec3 center_to_point = vec3_sub(*intersectionPoint, *cylinder->origin); // Vector from cylinder center to intersection point
    center_to_point.y = 0; // For a vertical cylinder, the normal's y-component is zero
    normalise(&center_to_point);

    cylinder->normal = (t_vec3 *)malloc(sizeof(t_vec3));
    *cylinder->normal = center_to_point; // Assign the normal to the cylinder
}


t_vec3 raytraceCylinder(t_ray ray, t_cylinder cylinder, t_ray *lightObj, t_scene sceneObj, t_vec3 intersectionPoint)
{
    (void)ray;
    // Initialize a t_vec3 to hold the final light intensity.
    t_vec3 Ifinal;

    // Get the base color of the cylinder
    //t_vec3 baseColor = cylinder.color; // Use the color defined in the cylinder
    t_vec3 baseColor = {0.914, 0.588, 0.478};   //basic pink salmon color

    /*------------------------Ambient lighting----------------------------------*/
    float Kambient = 0.5f;                                                       // Ambient reflectivity of the cylinder's material
    float Ilight = 0.3f;                                                         // Ambient light intensity
    t_vec3 Iambient = {Kambient * Ilight, Kambient * Ilight, Kambient * Ilight}; // Ambient light color (assumed same intensity for RGB)

    /*------------------------Diffuse Lighting (Lambertian Reflection)------------*/
    float Kdiffuse = 0.5f;           // Diffuse reflectivity of the cylinder's material
    t_vec3 N = *cylinder.normal;     // Normal at the intersection point
    t_vec3 L = *lightObj->direction; // Light direction vector

    normalise(&L);                   // Normalize light direction
    float NdotL = fmax(0.0f, fmin(1.0f, dot(N, L)));

    // Apply the base color to the diffuse light color
    t_vec3 Idiffuse = {
        Kdiffuse * Ilight * NdotL * baseColor.x,
        Kdiffuse * Ilight * NdotL * baseColor.y,
        Kdiffuse * Ilight * NdotL * baseColor.z
    }; // Diffuse light color

    /*------------------------Specular Lighting (Phong Reflection Model)------------*/
    float Kspecular = 0.5f;                                           // Specular reflectivity (shininess) of the cylinder's material
    float n = 500;                                                     // Shininess factor
    t_vec3 R;                                                         // Reflected vector
    t_vec3 V = vec3_sub(intersectionPoint, *sceneObj.camera->origin); // View direction vector
    normalise(&V);                                                    // Normalize view direction

    // Compute the reflection vector R = 2 * dot(L, N) * N - L
    R = vec3_sub(scalarMult(N, 2.0f * dot(L, N)), L);
    normalise(&R); // Normalize reflection vector

    // Compute the dot product for specular reflection
    float RdotV = dot(R, V);
    RdotV = fmax(0.0f, RdotV); // Ensure it's non-negative

    // Calculate specular light intensity
    t_vec3 Ispecular = {Kspecular * Ilight * pow(RdotV, n), Kspecular * Ilight * pow(RdotV, n), Kspecular * Ilight * pow(RdotV, n)};

    /*------------------------Final color combination----------------------------*/
    Ifinal.x = fminf(fmaxf(Iambient.x + Idiffuse.x + Ispecular.x, 0.0f), 1.0f);
    Ifinal.y = fminf(fmaxf(Iambient.y + Idiffuse.y + Ispecular.y, 0.0f), 1.0f);
    Ifinal.z = fminf(fmaxf(Iambient.z + Idiffuse.z + Ispecular.z, 0.0f), 1.0f);


    //Return the final lighting result as a t_vec3
    //printf("Ifinal: %f, %f, %f\n", Ifinal.x, Ifinal.y, Ifinal.z);
    return Ifinal;

}
