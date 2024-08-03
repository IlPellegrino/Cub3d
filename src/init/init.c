/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:50:29 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 17:02:53 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	create_img(void *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->pixel_ptr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_len, &img->endian);
}

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
	settings->radians_fov = RADIANS_FOV;
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
	cubed->keys->page_down = 0;
	cubed->keys->page_up = 0;
	cubed->gui = malloc(sizeof(t_gui));
	cubed->gui->open_door = 0;
	cubed->gui->close_door = 0;
	init_settings(cubed);
	init_texture(cubed);
	init_player(cubed);
	return (1);
}
