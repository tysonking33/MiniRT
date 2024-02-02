#include <stdio.h>
#include <math.h>

typedef struct s_vec{
    float x;
    float y;
    float z;
}   t_vec;

t_vec create_t_vec(float x, float y, float z)
{
    return (t_vec){x,y,z};
}

struct s_vec print_vec(struct s_vec vec)
{
    printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}

void change_vec(struct s_vec *vec)
{
    vec->x = 1000000;
}

t_vec vector_multi_k(t_vec v1, float k)
{
    return create_t_vec((v1.x * k),(v1.y * k),(v1.z * k));
}

float vector_dot_product(t_vec v1, t_vec v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) +(v1.z * v2.z));
}

float vector_length(t_vec vect)
{
    return sqrt(vector_dot_product(vect, vect));
}

void normalise_vector(struct s_vec *vector)
{
    float len = vector_length(*vector);
    if (!len)
    {
        *vector = create_t_vec(0,0,0);
    }
    else{

        *vector = vector_multi_k(*vector, 1/len);
    }
}

int main()
{
    t_vec vec1 = create_t_vec(52, 11, 321);
    print_vec(vec1);
    change_vec(&vec1);
    print_vec(vec1);
    normalise_vector(&vec1);
    print_vec(vec1);
}