/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 20:08:56 by ciusca           ###   ########.fr       */
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
	int		line_len;
}				t_img;

typedef	struct s_game
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_cl;
	int		ceiling_cl;
	int		ht;
	int		counter;
	int		p_flag;
	int		is_wall;
}				t_game;

typedef struct s_player
{
	int		x;
	int		y;
	float	angle;
	float	d_x; //delta x of the player
	float	d_y; //delta y of the player
	int		map_x;
	int		map_y;
	float	fov;
}				t_player;

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
	int			map_h;
	int			map_w;
	char		**map;
	void		*mlx;
	void		*win;
	t_img		*img;
	t_player	*player;
	t_raycast	*raycast;
	t_game		*game;
}				t_cubed;

#endif