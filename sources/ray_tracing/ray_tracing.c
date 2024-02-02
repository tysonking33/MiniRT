#include "../../includes/minirt.h"
#include "../../includes/error.h"
#include "../../includes/objects.h"

t_plane *get_projection_plane(float scene_w, float scene_h, float angle)
{
    t_plane *proj;
    float ratio;

    proj = (t_plane*)malloc(sizeof(t_plane));
    if (proj == NULL)
        exit_on_error(-1, ERR_MALLOC);
    
    float ratio = scene_w / scene_h;

    proj->width = 2 * (tan(angle/2 * M_PI / 180));
    proj->height = proj->width / ratio;
    proj->x_pix = proj->width / scene_w;
    proj->y_pix = proj->height / scene_h;

    return proj;
}

void ray_tracing(t_minirt *minirt)
{
    int mlx_x;
    int mlx_y;
    float x_angle;
    float y_angle;
    float x_ray;
    float y_ray;
    t_vector *ray;
    t_plane *proj;
    t_point point;

    mlx_y = 0;
    proj = get_projection_plane(WIN_WIDTH, WIN_HEIGHT, minirt.scene->camera->angle);
    y_angle = WIN_HEIGHT / 2.0;
    while (y_angle >= (WIN_HEIGHT / -2.0))
    {
        mlx_x = 0;
        y_ray = y_angle *proj->y_pix;
        x_angle = WIN_WIDTH / -2.0;
        while (x_angle <= (WIN_WIDTH / 2.0))
        {
            x_ray = x_angle * proj->x_pix;
            *ray = create_t_vec(x_ray, y_ray, -1.0);
            normalise_vector(ray);
            object_intersections(minirt, minirt->objs, ray, &point);
            my_mlx_pixel_put(minirt, mlx_x, mlx_y, point.color);
            free(ray);
            mlx_x++;
            x_angle++;

        }
        mlx_y++;
        y_angle--;
    }
}