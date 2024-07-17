/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/16 20:29:29 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_wall(t_cubed *cubed, int x, int y)
{
	(void)cubed;
	(void)x;
	(void)y;
	/*
	todo: devide the pos by tile size and round it
		  then check if the result is a 1 in the map
	*/
	
	return (1);
}

/* temp function*/
char **set_map(void)
{
	char	**map;

	map = ft_calloc(sizeof(char*), 10);
	map[0] = ft_strdup("111111111111111111111");
	map[1] = ft_strdup("100000000000000000001");
	map[2] = ft_strdup("100000000000000000001");
	map[3] = ft_strdup("100000000000000000001");
	map[4] = ft_strdup("100000000000000000001");
	map[5] = ft_strdup("100000000000000000001");
	map[6] = ft_strdup("10000000000N000000001");
	map[7] = ft_strdup("100000000000000000001");
	map[8] = ft_strdup("100000000000000000001");
	map[9] = ft_strdup("111111111111111111111");
	return (map);
	
}

void draw_player(t_cubed *cubed, int x, int y)
{
	t_img *player;
	
	player = create_img(cubed->mlx, PLAYER_SIZE, red);
	mlx_put_image_to_window(cubed->mlx, cubed->win, player->img, x, y);
}

void	draw_map(t_cubed *cubed, char **map)
{
	int		i;
	int		j;
	t_img 	*wall;
	t_img 	*floor;
	t_player *p;
	
	p = cubed->player;
	floor = create_img(cubed->mlx, TILE_SIZE, black);
	wall = create_img(cubed->mlx, TILE_SIZE, white);
	i = -1;
	j = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(cubed->mlx, cubed->win, wall->img, j * TILE_SIZE, i * TILE_SIZE);
			else if (map[i][j] == '0' || map[i][j] == 'N')
				mlx_put_image_to_window(cubed->mlx, cubed->win, floor->img, j * TILE_SIZE, i * TILE_SIZE);
		}
	}
}


int	game_loop(t_cubed *cubed)
{
	(void)cubed;
	//raycasting algorithm
	
	return (1);
}