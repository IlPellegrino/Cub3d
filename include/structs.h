/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/30 19:36:15 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct	s_settings
{
	int	mini_size;
	int	player_speed;
	int	rotation_speed;
	int	player_size;
	int	fov;
	int	crosshair_color;
}			t_settings;

typedef	struct	s_img
{
	char	*name;
	char	*pixel_ptr;
	void	*img;
	int		*data;
	int		w;
	int		h;
	int		bits_per_pixel; 
	int		endian;
	int		line_len;
	int		frame;
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
	int		anim_state;
	int		mouse_x;
	int		mouse_y;
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
	int	plus;
	int	minus;
	int	left;
	int	right;
	int	esc;
	int	pause;
	int space;
}				t_keys;

typedef struct s_player
{
	int		map_x;
	int		map_y;
	float	angle;
	double	x;
	double	y;
	double	d_x; //delta x of the player
	double	d_y; //delta y of the player
}				t_player;

typedef struct s_raycast
{
	int		r;   //radiuds
	int		mx;  //map x
	int 	my;	 //map y
	int		dof; //depht of field
	float	ra;  //ray angle
	float	rx;  //ray x
	float	ry;  //ray y
	double	vx;
	double	vy;
	double	hx;
	double	hy;
	double	stepX;
	double	stepY;
	double 	verX;
	double	horX;
	double 	horY;
	double 	verY;
}			t_raycast;

typedef struct s_gui
{
	int		open_door;
	int		close_door;
}			t_gui;

typedef struct	s_cubed
{
	int			map_h;
	int			map_w;
	char		**map;
	void		*mlx;
	void		*win;
	t_img		*img;
	t_player	*player;
	t_img		texture[5];
	t_img		door_anim[FRAME_NUMBER];
	time_t		time;
	t_raycast	*raycast;
	t_game		*game;
	t_keys		*keys;
	t_settings	*settings;
	t_gui		*gui;
}				t_cubed;

#endif