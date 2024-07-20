/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/20 13:18:34 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct	s_img
{
	char	*name;
	char	*pixel_ptr;
	void	*img;
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
	char	**cub;
	int		floor_cl;
	int		ceiling_cl;
	int		ht;
	int		wd;
	int		counter;
	int		p_flag;
	int		is_wall;
}				t_game;

typedef	struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}				t_keys;

typedef struct s_player
{
	double		x;
	double		y;
	float	angle;
	double	d_x; //delta x of the player
	double	d_y; //delta y of the player
	int		map_x;
	int		map_y;
	float	fov;
}				t_player;

typedef struct s_raycast
{
	int		r;   //radiuds
	int		mx;  //map x
	int 	my;	 //map y
	int		mp;	 //map position
	int		dof; //depht of field
	float	ra;  //ray angle
	float	rx;  //ray x
	float	ry;  //ray y
	float	xo;  //x offset
	float	yo;  //y offset
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
	t_keys		*keys;
}				t_cubed;

#endif