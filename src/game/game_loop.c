/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/22 19:33:26 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"


/* temp function*/
char **set_map(void)
{
	char	**map;

	map = ft_calloc(sizeof(char*), 10 + 1);
	map[0] = ft_strdup("111111111111111111111");
	map[1] = ft_strdup("100000000000000000001");
	map[2] = ft_strdup("100000000000000000001");
	map[3] = ft_strdup("100000111000000000001");
	map[4] = ft_strdup("100000100000000000001");
	map[5] = ft_strdup("100000000000000000001");
	map[6] = ft_strdup("10000001110N000000001");
	map[7] = ft_strdup("100000000000000000001");
	map[8] = ft_strdup("100000110000000000001");
	map[9] = ft_strdup("111111111111111111111");
	return (map);
	
}


void	draw_shape(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;
	int	start_x;
	
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

void draw_player(t_img *img, int x, int y)
{
	draw_shape(img, x - (PLAYER_SIZE / 2), y - (PLAYER_SIZE / 2), PLAYER_SIZE, yellow);
}
void	minimap(t_img *img, char **map)
{
	int			i;
	int			j;
	
	i = -1;
	j = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				draw_shape(img, j * MINI_SIZE, i * MINI_SIZE, MINI_SIZE, white);
			else
				draw_shape(img, j * MINI_SIZE, i * MINI_SIZE, MINI_SIZE, black);
		}
	}
}


int	game_loop(t_cubed *cubed)
{
	t_img		*img;
	
	img = cubed->img;
	if (cubed->keys->pause)
		return (0);
	mlx_destroy_image(cubed->mlx, cubed->img->img);
	create_img(cubed->mlx, cubed->img);
	load_texture(cubed);
	move_handler(cubed);
	rendering(cubed);
	minimap(img, cubed->map);
	//draw_player(img, cubed->player->x, cubed->player->y);
	mlx_put_image_to_window(cubed->mlx, cubed->win, img->img, 0, 0);
	return (1);
}
