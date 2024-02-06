/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:42:37 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/02 09:23:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800

# define MIN_DIST		0.0001
# define MAX_DIST		100000000.0

# define COL_RED		0x00D13632
# define COL_ORANGE		0x00E2571E
# define COL_YELLOW		0x00CDB924
# define COL_GREEN		0x00479E1B
# define COL_BLUE		0x001D829E
# define COL_VIOLET		0x00503FA9
# define COL_BLACK		0x002B2B2A

# include <stdio.h>
# include <math.h>
# include "structure_prototypes.h"
#include "error.h"
#include "objects.h"


/* vector functions */
t_vector ft_vector_rotate(t_vector vector, int clockwise);
t_vector create_t_vec(float x, float y, float z);
t_vector print_vec(t_vector vec);
void normalise_vector(t_vector *vector);
float vector_dot_product(t_vector v1, t_vector v2);
float point_distance(t_vector v1, t_vector v2);
t_vector vector_add_vector(t_vector v1, t_vector v2);
t_vector vector_subtract_vector(t_vector v1, t_vector v2);
t_vector vector_multi_k(t_vector v1, float k);
float vector_length(t_vector vect);

/* errors_n_exits.c */
static void	ft_free_lights(t_scene *scene);
static void	ft_free_objects(t_scene *scene);
void	ft_free_scene(t_scene *scene);
void	ft_error(char *error_type, t_scene *scene);
void	ft_normal_error(char *error_type, t_vector *norm_v);

/* ray_tracing.c */
t_plane *get_projection_plane(float scene_w, float scene_h, float angle);
void ray_tracing(t_minirt *minirt);


/* objects/ambient.c */
void print_ambient(t_minirt *minirt);
void	ft_init_ambient(t_minirt *minirt);
void	ft_read_ambient(t_minirt *minirt, char *line);

/* objects/camera.c */
void	ft_free_camera(t_minirt *minirt);
void	ft_print_camera(t_minirt *minirt);
void	ft_init_camera(t_minirt *minirt);
void	ft_read_camera(t_minirt *minirt, char *line);


/* object/scone.c*/
static int	in_range(float num, float range);
static void	update_hit_point(t_intersection *hit, float dist, float m);
static float	get_dist(	t_object *obj,
							t_vector ray, t_eq body, t_vector origin);
static inline float	find_dists_co(	t_object *obj,
									t_vector ray, t_eq eq, t_vector origin);


#endif