/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 18:17:24 by ciusca           ###   ########.fr       */
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
	return (1);
}

int	init_data(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D");
	cubed->img = malloc(sizeof(t_img));
	create_img(cubed->mlx, cubed->img);
	cubed->raycast = malloc(sizeof (t_raycast));
	cubed->game = malloc(sizeof (t_game));
	if (!cubed->raycast || !cubed->game)
		return (0);
	cubed->raycast->dirX = -1;
	cubed->raycast->dirY = 0;
	cubed->raycast->posX = 22;
	cubed->raycast->posY = 12;
	init_player(cubed);
	//cubed->game = ft_calloc(sizeof(t_game), 1);
	return (1);
}
