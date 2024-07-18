/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/18 19:02:07 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_player(t_cubed *cubed)
{
	t_player	*p;

	cubed->player = malloc(sizeof(t_player));
	p = cubed->player;
	p->map_x = 3;
	p->map_y = 5;
	p->x = p->map_x * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	p->y = p->map_y * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	printf("player x = %d\nplayer y = %d\n", p->x, p->y);
	p->angle = 0;
	p->d_x = cos(p->angle) * 20;
	p->d_y = sin(p->angle) * 20;
	printf("delta x = %f\ndelta y = %f\n", p->d_x, p->d_y);
	return (1);
}

int	init_data(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->img = malloc(sizeof(t_img));
	cubed->win = 0;
	create_img(cubed->mlx, cubed->img);
	cubed->raycast = malloc(sizeof (t_raycast));
	cubed->game = ft_calloc(sizeof (t_game), 1);
	if (!cubed->raycast || !cubed->game)
		return (0);
	cubed->map = 0;
	cubed->raycast->dirX = -1;
	cubed->raycast->dirY = 0;
	cubed->raycast->posX = 22;
	cubed->raycast->posY = 12;
	init_player(cubed);
	return (1);
}
