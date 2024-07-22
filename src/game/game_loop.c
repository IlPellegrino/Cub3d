/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/22 20:15:50 by ciusca           ###   ########.fr       */
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
//draw a triagnle pointint to the player direction

void	draw_shape(t_img *img, double x, double y, int size, int color)
{
	int	i;
	int	j;
	int	start_x;
	
	printf("x = %f, y = %f\n", x, y);
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
	t_raycast	*ray;
	t_player	*p;

	p = cubed->player;
	ray = cubed->raycast;
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

	p = cubed->player;
	img = cubed->img;
	i = -1;
	
	while (++i < MINIMAP_SIZE)
	{
		j = -1;
		y = (p->y - MINI_SIZE / 2 + i) / 32;
		while (++j < MINIMAP_SIZE)
		{
			x = (p->x - MINI_SIZE / 2 + j) / 32;
			if (j < 5 || j > MINIMAP_SIZE - 6 || i < 5 || i > MINIMAP_SIZE - 6)
				color = eggplant;
			else if (x < 0 || y < 0 || y >= matrix_len(map) || x >= (int)ft_strlen(map[y]))
				color = claret;
			else if (map[y][x] == '1')
				color = lion;
			else
				color = snow;
			better_pixel_put(img, i, j, color);
		}
	}
	
}

void	minimap(t_cubed *cubed, char **map)
{
	draw_minimap(cubed, map);
	draw_shape(cubed->img, 97, 97, 5, rich_black);
}


int	game_loop(t_cubed *cubed)
{
	t_img		*img;
	t_player	*p;
	t_raycast	*ray;
	
	ray = cubed->raycast;
	p = cubed->player;
	img = cubed->img;
	if (cubed->keys->pause)
		return (0);
	mlx_destroy_image(cubed->mlx, cubed->img->img);
	create_img(cubed->mlx, cubed->img);
	move_handler(cubed);
	rendering(cubed);
	minimap(cubed, cubed->map);
	mlx_put_image_to_window(cubed->mlx, cubed->win, img->img, 0, 0);
	return (1);
}
