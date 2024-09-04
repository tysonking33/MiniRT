#include "../includes/Math.h"

struct s_vec3 vec3_sub(struct s_vec3 lhs, struct s_vec3 rhs)
{
    struct s_vec3 result = {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    return result;
}
struct s_vec3 vec3_add(struct s_vec3 lhs, struct s_vec3 rhs)
{
    struct s_vec3 result = {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    return result;
}
struct s_vec3 scalarMult(struct s_vec3 v, float k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return v;
}

float dot(struct s_vec3  a, struct s_vec3  b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z; 
}

float vec3_magnitude(struct s_vec3 a)
{
    return sqrt(pow(a.x,2) + pow(a.y,2) +  pow(a.z,2));
}

struct s_vec3 normalize(struct s_vec3 v)
{
    float magnitude = vec3_magnitude(v);
    struct s_vec3 result = {0.f, 0.f, 0.f};
    if (magnitude != 0){
        result.x = v.x/magnitude;
        result.y = v.y/magnitude;
        result.z = v.z/magnitude;
    }
    else
    {
        printf("(normalize): divided by 0\n");
    }
    return result;

}

float intersectRaySphere(struct s_ray ray, struct s_sphere sphere)
{
    struct s_vec3 L = vec3_sub(*(ray.origin), *(sphere.origin));
    float a = dot(*(ray.origin), *(ray.direction));
    float b = 2 * (dot(L, *(ray.direction)));
    float c = (dot(L, L)) - pow(sphere.radius, 2);
    float discrim = pow(b,2) - 4 * a * c;

    if (discrim > 0)
    {
        printf("2 intersection points, ray passed through sphere\n");
    }
    else if (discrim == 0)
    {
        printf("1 intersection point, ray is tangent to sphere\n");
    }
    else
    {
        printf("No intersection");
    }
    return discrim;
}

struct s_vec3 *findPointOfRaySphereIntersect(struct s_ray ray, struct s_sphere sphere, float discriminant)
{
    struct s_vec3 L = vec3_sub(*(ray.origin), *(sphere.origin));
    float a = dot(*(ray.origin), *(ray.direction));
    float b = 2 * (dot(L, *(ray.direction)));
    //float c = (dot(L, L)) - pow(sphere.radius, 2);

    float tPlus = (-b + sqrt(discriminant))/ (2*a);
    float tSub = (-b - sqrt(discriminant))/ (2*a);

    int size = 0;
    if (tPlus >= 0)
    {size++;}
    if (tSub >= 0)
    {size++;}

    struct s_vec3* array = (struct s_vec3*)malloc(size * sizeof(struct s_vec3));

    int count = 0;
    if (tPlus >= 0)
    {
        struct s_vec3 temp_vec = rayAt(ray, tPlus);
        array[count] = temp_vec;
    }
    if (tSub >= 0)
    {
        struct s_vec3 temp_vec = rayAt(ray, tSub);
        array[count] = temp_vec;
    }

    return array;
}


struct s_vec3 computeNormalSphere(struct s_vec3 intersectionPoint, struct s_sphere sphere)
{
    struct s_vec3 sphereNormal = {intersectionPoint.x - sphere.origin->x, intersectionPoint.y - sphere.origin->y, intersectionPoint.z - sphere.origin->z};
    return scalarMult(sphereNormal, sphere.radius);
}

struct s_vec3 rayAt(struct s_ray ray, float t)
{
    return vec3_add(*(ray.origin), scalarMult(*(ray.direction), t));
}

