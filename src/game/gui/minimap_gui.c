/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_gui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:04:24 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 15:55:25 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

int	get_map_color(char **map, int x, int y)
{
	int	color;

	if (x < 0 || y < 0 || y >= matrix_len(map)
		|| x >= (int)ft_strlen(map[y])
		|| map[y][x] == ' ')
		color = claret;
	else if (map[y][x] == '1')
		color = lion;
	else if (map[y][x] == 'D')
		color = purple;
	else if (map[y][x] == 'C')
		color = green;
	else
		color = snow;
	return (color);
}

int	get_point(t_player *p, t_settings *settings, int pos)
{
	int		point;
	double	plyr_x;
	double	plyr_y;

	plyr_x = p->x / TILE_SIZE;
	plyr_y = p->y / TILE_SIZE;
	plyr_x = plyr_x * settings->mini_size;
	plyr_y = plyr_y * settings->mini_size;
	point = (plyr_y - MINIMAP_SIZE / 2 + pos) / settings->mini_size;
	return (point);
}

void	draw_horizontal(int y, int i, double plyr_x, t_cubed *cubed)
{
	int			color;
	t_settings	*settings;
	t_img		*img;
	int			j;
	int			x;

	settings = cubed->settings;
	img = cubed->img;
	j = -1;
	while (++j < MINIMAP_SIZE)
	{
		x = (plyr_x - MINIMAP_SIZE / 2 + j) / settings->mini_size;
		if (j < 5 || j > MINIMAP_SIZE - 6 || i < 5 || i > MINIMAP_SIZE - 6)
			color = eggplant;
		else
			color = get_map_color(cubed->map, x, y);
		better_pixel_put(img, j, i, color);
	}
}

void	draw_minimap(t_cubed *cubed)
{
	int			y;
	int			i;
	double		plyr_x;
	double		plyr_y;
	t_settings	*settings;

	settings = cubed->settings;
	i = -1;
	while (++i < MINIMAP_SIZE)
	{
		plyr_x = cubed->player->x / TILE_SIZE;
		plyr_y = cubed->player->y / TILE_SIZE;
		plyr_x = plyr_x * settings->mini_size;
		plyr_y = plyr_y * settings->mini_size;
		y = (plyr_y - MINIMAP_SIZE / 2 + i) / settings->mini_size;
		draw_horizontal(y, i, plyr_x, cubed);
	}
}

void	minimap(t_cubed *cubed)
{
	double		x_len;
	double		y_len;
	int			start_pos[2];

	start_pos[0] = 100;
	start_pos[1] = 100;
	draw_minimap(cubed);
	draw_shape(cubed->img, 98, 98, 5);
	x_len = cubed->player->d_x * 10;
	y_len = cubed->player->d_y * 10;
	draw_line(cubed->img, start_pos, (int)(100 + x_len),
		(int)(100 + y_len));
}
