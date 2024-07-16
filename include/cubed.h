/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:16:21 by nromito           #+#    #+#             */
/*   Updated: 2024/07/16 20:38:51 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include "defines.h"
# include "structs.h"
# include "colors.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>

void	draw_map(t_cubed *cubed, char **map);
char 	**set_map(void);
void 	draw_player(t_cubed *cubed, int x, int y);

// utils //
int		ft_close(t_cubed *cubed, int err_status);
int 	ft_error(char *error, t_cubed *cubed);
t_img	*create_img(void *mlx, int size, int color);

// events //
//int		key_events(int key, t_cubed *cubed);

/* init */
int		init_data(t_cubed *cubed);

/* parsing */
int		parsing(char **argv, int argc, t_cubed *cubed);
int		check_file(char *map, t_cubed *cubed);

/* raycaster */

/* game loop */
int		game_loop(t_cubed *cub);
int		events(int key, t_cubed *cubed);

/* utils */
//tutti qua coglione

#endif