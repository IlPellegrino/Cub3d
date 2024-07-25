/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/25 19:08:33 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	draw_shape(t_img *img, double x, double y, int size, int color)
{
	int	i;
	int	j;
	int	start_x;
	
	//printf("x = %f, y = %f\n", x, y);
	start_x = x;
	j = -1;
	while (++j < size)
	{
		i = -1;
		x = start_x;
		while (++i < size)
		{
			better_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void draw_player(t_img *img, double x, double y, t_cubed *cubed)
{
	double		plyr_x;
	double		plyr_y;
	// t_raycast	*ray;
	t_player	*p;

	p = cubed->player;
	// ray = cubed->raycast;
	plyr_x = x * MINI_SIZE;
	plyr_y = y * MINI_SIZE; 

	draw_line(img, plyr_x, plyr_y, (plyr_x + p->d_x * 10), (plyr_y + p->d_y * 10), red);	
	
	draw_shape(img, plyr_x  - PLAYER_SIZE / 2, plyr_y  - PLAYER_SIZE / 2, PLAYER_SIZE, yellow);
	// draw player pov
}

#define MINIMAP_SIZE 200

void	draw_minimap(t_cubed *cubed, char **map)
{

	int		i;
	int		j;
	t_img	*img;
	t_player *p;
	int		color;
	int		x;
	int		y;
	t_settings *settings;

	settings = cubed->settings;
	p = cubed->player;
	img = cubed->img;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		double plyr_x = p->x / TILE_SIZE;
		double plyr_y = p->y / TILE_SIZE;
		plyr_x = plyr_x * settings->mini_size;
		plyr_y = plyr_y * settings->mini_size;
		y = (plyr_y - MINIMAP_SIZE / 2 + i) / settings->mini_size;
		while (++j < MINIMAP_SIZE)
		{
			x = (plyr_x - MINIMAP_SIZE / 2 + j) / settings->mini_size;
			if (j < 5 || j > MINIMAP_SIZE - 6 || i < 5 || i > MINIMAP_SIZE - 6)
				color = eggplant;
			else if (x < 0 || y < 0 || y >= matrix_len(map) || x >= (int)ft_strlen(map[y]))
				color = claret;
			else if (map[y][x] == '1')
				color = lion;
			else if (map[y][x] == 'D')
				color = purple;
			else if (map[y][x] == 'C')
				color = green;
			else
				color = snow;
			better_pixel_put(img, j, i, color);
		}
	}
	
}

void	minimap(t_cubed *cubed, char **map)
{
	t_settings	*sett;
	double		x_len;
	double		y_len;

	sett = cubed->settings;
	draw_minimap(cubed, map);
	draw_shape(cubed->img, 98, 98, 5, rich_black);
	// scale d_x and d_y to minimap size increasing and decreasing to sett->mini_siz
	x_len = cubed->player->d_x * 10;
	y_len = cubed->player->d_y * 10;
	draw_line(cubed->img, 100, 100, (int)(100 +  x_len), (int)(100 + y_len), rich_black);
}

void	draw_crosshair(t_cubed	*cubed)
{
	int	i;
	int	j;
	int	color;
	int	x;
	int	y;

	x = WIDTH / 2 - 1;
	y = HEIGHT / 2 - CROSS_SIZE / 2;

	color = white;
	i = -1;
	
	while (++i < CROSS_SIZE)
	{
		j = -1;
		while (++j < 2)
			better_pixel_put(cubed->img, x + j, y + i, color);
	}
	x  = WIDTH / 2 - CROSS_SIZE / 2;
	y = HEIGHT / 2 - 1;
	i = -1;
	j = -1;
	while (++i < CROSS_SIZE)
	{
		j = -1;
		while (++j < 2)
			better_pixel_put(cubed->img, x + i, y + j, color);
	}
	
}

#include <X11/Xlib.h>

int	game_loop(t_cubed *cubed)
{
	t_img		*img;

	img = cubed->img;
	if (cubed->keys->pause)
		return (0);
	mlx_destroy_image(cubed->mlx, cubed->img->img);
	create_img(cubed->mlx, cubed->img);
	move_handler(cubed);
	interactable(cubed);
	rendering(cubed);
	minimap(cubed, cubed->map);
	draw_crosshair(cubed);
	mlx_put_image_to_window(cubed->mlx, cubed->win, img->img, 0, 0);
	return (1);
}
