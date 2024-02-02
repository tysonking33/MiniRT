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


#endif