/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:16:21 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 00:10:36 by ciusca           ###   ########.fr       */
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

// utils //
int		ft_close(t_cubed *cubed, int err_status);
int 	ft_error(char *error, t_cubed *cubed);
void	create_img(t_img *img, void *mlx, int size, int color);

// events //
int		key_events(int key, t_cubed *cubed);

/* init */
int		screen_setting(t_cubed *cubed);

/* parsing */
int		parsing(char **argv, int argc);
int		check_map(char *map);

/* raycaster */

/* utils */
//tutti qua coglione

#endif