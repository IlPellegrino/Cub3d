/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 15:08:49 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_player(t_cubed *cubed)
{
	(void)cubed;
	return (1);
}

int	init_data(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D");
	cubed->raycast = malloc(sizeof (t_raycast));
	cubed->player = malloc(sizeof(t_player));
	if (!cubed->raycast || !cubed->player)
		return (0);
	cubed->raycast->dirX = -1;
	cubed->raycast->dirY = 0;
	cubed->raycast->posX = 22;
	cubed->raycast->posY = 12;
	return (1);
}
