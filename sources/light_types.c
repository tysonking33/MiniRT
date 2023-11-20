#include "../includes/minirt.h"

float *find_reflection_vector(float *incident, float *normal)
{
    //Reflection=Incident−2×(Incident⋅Normal)×NormalReflection=Incident−2×(Incident⋅Normal)×Normal
    float *reflection_vector = (float *)malloc(3*sizeof(incident));
    return reflection_vector;
}

float *find_refraction_vector(float *incident, float *normal)
{
    float *refraction_vector = (float *)malloc(3*sizeof(incident));
    return refraction_vector;
}