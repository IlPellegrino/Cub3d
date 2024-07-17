/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 11:31:22 by nromito          ###   ########.fr       */
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
	char	**world_map;
	int		floor_cl;
	int		ceiling_cl;
	int		ht;
	int		counter;
	int		p_flag;
	int		is_wall;
}				t_game;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
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
	void		*img;
	t_player	*player;
	t_raycast	*raycast;
	t_game		*game;
}				t_cubed;

#endif