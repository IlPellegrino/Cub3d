/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/14 23:59:46 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	create_images(t_cubed *cubed)
{
	cubed->img->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->img)
		ft_error("Image creation failed\n", cubed);
	return (1);
}

int	init_vars(t_cubed *cubed)
{
	cubed->x_player = 300;
	cubed->y_player = 300;
	cubed->raycast = malloc(sizeof (t_raycast));
	cubed->game = malloc(sizeof (t_game));
	if (!cubed->raycast || !cubed->game)
		ft_error("Allocation failed\n", cubed);
	cubed->game->is_wall = 0;
	cubed->raycast->dirX = -1;
	cubed->raycast->dirY = 0;
	cubed->raycast->posX = 22;
	cubed->raycast->posY = 12;
	return (1);
}

int	screen_setting(t_cubed *cubed)
{
	init_vars(cubed);
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		ft_error("Init failed\n", cubed);
	cubed->window = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cubed->window)
		ft_error("Window creation failed\n", cubed);
	//create_images(cubed);
	//cubed->addr = mlx_get_data_addr(cubed->img, &cubed->bits_per_pixel,
	//		&cubed->line_length, &cubed->endian);
	return (1);
}
