/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:16:21 by nromito           #+#    #+#             */
/*   Updated: 2024/07/25 16:58:34 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include "defines.h"
# include "structs.h"
# include "errors.h"
# include "colors.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>

char 	**set_map(void);
/**======================
 *?    	CLOSE / ERROR
 *========================**/
int		ft_close(t_cubed *cubed, int err_status);
int 	ft_error(char *error, t_cubed *cubed);

/**======================
 *?    		UTILS
 *========================**/
int		is_wall(t_cubed *cubed, double x, double y);
int		create_trgb(int t, int r, int g, int b);
void 	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);
void	better_pixel_put(t_img *img, int x, int y, int color);

/**======================
 *?    		INIT
 *========================**/
int		init_data(t_cubed *cubed);
void	create_img(void *mlx, t_img *img);
//void	draw_shape(t_img *img, int x, int y, int size,  int color);

/**======================
 *?    	  PARSING
 *========================**/
int		parsing(char **argv, int argc, t_cubed *cubed);
int		check_file(char *map, t_cubed *cubed);
int		count_map_columns(int fd, t_cubed *cubed);
int		count_width(t_cubed *cubed);
int		check_chars(char **map, int l, int col);
void	check_map(t_cubed *cubed);
int		surfaces_check(char *line, t_cubed *cubed);
int		textures_check(char *line, t_cubed *cubed);
int		check_colors(char **color, t_cubed *cubed, int surface);
int 	is_acceptable(char c);
int		is_legal(char c);

/**======================
 *?    		GAME
 *========================**/
int		game_loop(t_cubed *cub);
void    rendering(t_cubed *cubed);
void 	draw_player(t_img *img, double x, double y, t_cubed *cubed);
void	minimap(t_cubed *cubed, char **map);
void	interactable(t_cubed *cubed);
/**======================
 *?    	 MOVEMENT
 *========================**/
int		move_handler(t_cubed *cubed);
int		validate_position(t_cubed *cubed, double new_x, double new_y);

/**======================
 *?    		KEYS
 *========================**/
int		key_press(int pressed, t_keys *keys);
int		key_release(int realesed, t_keys *keys);

/**======================
 *?    	  TEXTURE
 *========================**/
int		get_texture(t_cubed *cubed);
void	load_texture(t_cubed *cubed);

#endif