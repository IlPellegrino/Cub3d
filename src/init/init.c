/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/24 14:26:34 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_player(t_cubed *cubed)
{
	t_player	*p;

	cubed->player = malloc(sizeof(t_player));
	p = cubed->player;
	p->map_x = 6;
	p->map_y = 4;
	p->x = p->map_x * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	p->y = p->map_y * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	p->angle = NORTH;
	p->d_x = cos(p->angle);
	p->d_y = sin(p->angle);
	//draw_line(cubed->img, p->x, p->y, p->x + p->d_x * 50, p->y + p->d_y * 50, 0x00FF00);
	return (1);
}

void	init_settings(t_cubed *cubed)
{
	t_settings	*settings;

	cubed->settings = malloc(sizeof(t_settings));
	settings = cubed->settings;
	settings->mini_size = MINI_SIZE;
	settings->player_speed = PLAYER_SPEED;
	settings->rotation_speed = ROTATION_SPEED;
	settings->player_size = PLAYER_SIZE;
	settings->fov = FOV;
}

int	init_data(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->img = malloc(sizeof(t_img));
	cubed->win = 0;
	create_img(cubed->mlx, cubed->img);
	cubed->raycast = malloc(sizeof (t_raycast));
	cubed->game = ft_calloc(sizeof (t_game), 1);
	cubed->map = 0;
	cubed->game->counter = 0;
	if (!cubed->raycast || !cubed->game)
		return (0);
	cubed->keys = ft_calloc(sizeof(t_keys), 1);
	cubed->keys->space = 0;
	cubed->texture[0].w = WIDTH;
	cubed->texture[0].h = HEIGHT;
	cubed->texture[1].w = WIDTH;
	cubed->texture[1].h = HEIGHT;
	cubed->texture[2].w = WIDTH;
	cubed->texture[2].h = HEIGHT;
	cubed->texture[3].w = WIDTH;
	cubed->texture[3].h = HEIGHT;
	init_settings(cubed);
	init_player(cubed);
	return (1);
}
