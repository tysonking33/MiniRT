#include "../includes/Math.h"

t_vec3 vec3_sub(t_vec3 lhs, t_vec3 rhs)
{
    t_vec3 result = {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    return result;
}
t_vec3 vec3_add(t_vec3 lhs, t_vec3 rhs)
{
    t_vec3 result = {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    return result;
}
t_vec3 scalarMult(t_vec3 v, float k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return v;
}

t_vec3 scalarAdd(t_vec3 v, float k)
{
    v.x += k;
    v.y += k;
    v.z += k;
    return v;
}

float dot(t_vec3 a, t_vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_magnitude(t_vec3 a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

t_vec3 vec3_normalize(t_vec3 v)
{
    float magnitude = vec3_magnitude(v);
    t_vec3 result = {0.f, 0.f, 0.f};
    if (magnitude != 0)
    {
        result.x = v.x / magnitude;
        result.y = v.y / magnitude;
        result.z = v.z / magnitude;
    }
    else
    {
        //printf("(normalize): divided by 0\n");
    }
    return result;
}

float intersectRaySphere(t_ray ray, t_sphere sphere) {
    // Vector from ray origin to the center of the sphere
    t_vec3 L = vec3_sub(*(ray.origin), *(sphere.origin));

    // Coefficients of the quadratic equation
    float a = dot(*(ray.direction), *(ray.direction));      // a = dot(D, D)
    float b = 2.0f * dot(L, *(ray.direction));              // b = 2 * dot(L, D)
    float c = dot(L, L) - powf(sphere.radius, 2);           // c = dot(L, L) - r^2

    // Discriminant of the quadratic equation
    float discriminant = powf(b, 2) - 4 * a * c;

    // If discriminant is negative, there's no real solution (no intersection)
    if (discriminant < 0) {
        return -1.0f;
    }

    // Calculate the two solutions (t0 and t1 are the distances along the ray)
    float sqrtDiscriminant = sqrtf(discriminant);
    float t0 = (-b - sqrtDiscriminant) / (2 * a);
    float t1 = (-b + sqrtDiscriminant) / (2 * a);

    //printf("a: %f, b: %f, c: %f, discriminant: %f\n", a, b, c, discriminant);

    return sqrtDiscriminant;

    
    // We want the closest positive t value (smallest t > 0)
    if (t0 > 0 && t1 > 0) {
        return (t0 < t1) ? t0 : t1;  // Return the smaller positive t
    } else if (t0 > 0) {
        return t0;  // t0 is the only positive intersection
    } else if (t1 > 0) {
        return t1;  // t1 is the only positive intersection
    } else {
        return -1.0f;  // Both t0 and t1 are negative, so the intersection is behind the camera
    }
}



t_vec3 computeNormalSphere(t_vec3 intersectionPoint, t_sphere sphere)
{
    t_vec3 sphereNormal = {intersectionPoint.x - sphere.origin->x, intersectionPoint.y - sphere.origin->y, intersectionPoint.z - sphere.origin->z};
    return scalarMult(sphereNormal, sphere.radius);
}

t_vec3 rayAt(t_ray ray, float t)
{
    return vec3_add(*(ray.origin), scalarMult(*(ray.direction), t));
}

float maxft(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

float minft(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

t_vec3 createVec3(float x, float y, float z)
{
    t_vec3 result = {x, y, z};

    return result;

}

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



void printVec3(char *string, t_vec3 vector)
{
    printf("%s: x:%f, y:%f, z:%f", string, vector.x, vector.y, vector.z);
}
