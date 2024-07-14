/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/14 23:58:59 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct	s_img
{
	char	*name;
	char	*pixel_ptr; //pointer to the pixels 
	void	*img; // a pointer to the image
	int		bits_per_pixel; 
	int		endian;
	int		line_len; //
}				t_img;

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
	int			x_player; // x plyaer postion
	int			y_player; // y player position
	void		*mlx;
	void		*window;
	t_img		*img;
	t_raycast	*raycast;
	t_game		*game;
}				t_cubed;

#endif