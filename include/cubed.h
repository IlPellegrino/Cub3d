/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/11 18:52:54 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "colors.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

#define HEIGHT 293
#define WIDTH 640

typedef	struct	s_image
{
	char	*name;
	int		size;
	//add if needed
}				t_image;

typedef	struct s_game
{
	char	**map;
	int		is_wall;
	
}				t_game;


typedef struct s_raycast
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	fov;
	double	ray_x;
	double	ray_y;
}			t_raycast;

typedef struct	s_cubed
{
	t_game	*s_raycast;
}				t_cubed;



#endif