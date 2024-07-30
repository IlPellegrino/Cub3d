/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/30 18:34:10 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_player(t_cubed *cubed)
{
	t_player	*p;

	p = cubed->player;
	p->x = p->map_x * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	p->y = p->map_y * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	p->d_x = cos(p->angle);
	p->d_y = sin(p->angle);
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

int	init_texture(t_cubed *cubed)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cubed->texture[i].w = WIDTH;
		cubed->texture[i].h = HEIGHT;
	}
	return (1);
}

int	partial_init(t_cubed *cubed)
{
	int	i;

	i = -1;
	cubed->player = malloc(sizeof(t_player));
	if (!cubed->player)
		ft_error("Error: malloc failed\n", cubed);
	cubed->game = ft_calloc(sizeof (t_game), 1);
	cubed->map = 0;
	cubed->game->counter = 0;
	cubed->img = 0;
	cubed->win = 0;
	cubed->raycast = 0;
	cubed->keys = 0;
	cubed->mlx = 0;
	while (++i < 5)
		cubed->texture[i].img = 0;
	return (1);
}

int	init_data(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	cubed->img = malloc(sizeof(t_img));
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D");
	create_img(cubed->mlx, cubed->img);
	cubed->raycast = malloc(sizeof (t_raycast));
	if (!cubed->raycast)
		return (0);
	cubed->keys = ft_calloc(sizeof(t_keys), 1);
	cubed->keys->space = 0;
	cubed->gui = malloc(sizeof(t_gui));
	cubed->gui->open_door = 0;
	cubed->gui->close_door = 0;
	init_settings(cubed);
	init_texture(cubed);
	init_player(cubed);
	return (1);
}
