/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 17:26:11 by ciusca           ###   ########.fr       */
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
	if (cubed->raycast)
		return (0);
	cubed->game = malloc(sizeof (t_game));
	if (!cubed->raycast || !cubed->game)
		return (0);
	cubed->game->is_wall = 0;
	cubed->raycast->dirX = -1;
	cubed->raycast->dirY = 0;
	cubed->raycast->posX = 22;
	cubed->raycast->posY = 12;
	cubed->player = ft_calloc(sizeof(t_player), 1);
	cubed->game = ft_calloc(sizeof(t_game), 1);
	return (1);
}
