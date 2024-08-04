/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 22:45:08 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* struct that stores all the variables that can be changed during runtime */
typedef struct s_settings
{
	int		mini_size;
	int		player_speed;
	int		rotation_speed;
	int		player_size;
	int		fov;
	double	radians_fov;
}			t_settings;

/* struct that stores all the information for the texture and the screen */
typedef struct s_img
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

/* struct for drawing the vertical lines to create the walls */
typedef struct s_wall
{
	int		wall_top;
	int		wall_bottom;
	int		wall_height;
	int		tex_x;
	double	tex_pos;
	double	tex_step;
	double	final_dist;
}			t_wall;

/* struct that stores all the main data of the game */
typedef struct s_game
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
	int		frame;
	int		anim_state;
	int		mouse_x;
	int		mouse_y;
	int		counter;
	int		p_flag;
	int		is_wall;
}				t_game;

/* struct to map the keys that can be pressed during runtime */
typedef struct s_keys
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
	int	space;
	int	shift;
	int	page_up;
	int	page_down;
}				t_keys;

/* struct that stores the player's position and direction */
typedef struct s_player
{
	int		map_x;
	int		map_y;
	float	angle;
	double	x;
	double	y;
	double	d_x;
	double	d_y;
}				t_player;

/* struct that stores the raycasting variables */
typedef struct s_raycast
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	float	ra;
	float	rx;
	float	ry;
	double	ray_angle;
	double	vx;
	double	vy;
	double	hx;
	double	hy;
	double	a_tan;
	double	step_x;
	double	step_y;
	double	ver_x;
	double	ver_y;
	double	hor_x;
	double	hor_y;
	double	half_screen;
	double	half_fov;
	double	hor_stepx;
	double	hor_stepy;
	double	ver_stepx;
	double	ver_stepy;
	double	ra_tan;
}			t_raycast;

/* struct to show the key to press for opening/closing the door */
typedef struct s_gui
{
	int		open_door;
	int		close_door;
}			t_gui;

/* main struct */
typedef struct s_cubed
{
	int			map_w;
	int			map_h;
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