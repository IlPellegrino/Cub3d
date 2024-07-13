/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/12 16:21:47 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	t_raycast	*raycast;
	t_game		*game;
}				t_cubed;

#endif