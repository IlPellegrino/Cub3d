/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 17:47:37 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"


int	main(int argc, char **argv)
{
	t_cubed	cubed;
	
	(void)argc;
	(void)argv;
	init_data(&cubed);
	mlx_hook(cubed.win, KeyPress, KeyPressMask, &events, &cubed);
	mlx_hook(cubed.win, 17, 1L << 17, &ft_close, &cubed);
	mlx_loop_hook(cubed.mlx, &game_loop, &cubed);
	mlx_loop(cubed.mlx);
	//init_player(&cubed);
	
}
/*int	**map;

void	create_map(void)
{
	int	i;
	int	j;

	j = -1;
	int	h = 10;
	int	w = 16;
	i = -1;
	map = malloc(sizeof(int *) * h);
	while (++i < h)
	{
		j = -1;
		map[i] = malloc(sizeof(int *) * w);
		while (++j < w)
		{
			if (j == 0 || j == w - 1 || i == 0 || i == h - 1)
				map[i][j] = 1;
			else
				map[i][j] = 0;
			
		}
	}	
}
void	draw_map(t_cubed *cubed, int **map)
{
	t_img *wall;
	t_img *floor;
	wall = malloc(sizeof(t_img));
	floor = malloc(sizeof(t_img));
	create_img(wall, cubed->mlx, WALL_SIZE, 0x0000ff);
	create_img(floor, cubed->mlx, WALL_SIZE, 0xffffff);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (map[i][j] == 1)
				mlx_put_image_to_window(cubed->mlx, cubed->win, wall->img, j * (WALL_SIZE + 1) , i * (WALL_SIZE + 1));
			else if (map[i][j] == 0)
				mlx_put_image_to_window(cubed->mlx, cubed->win, floor->img, j * (WALL_SIZE + 1) , i * (WALL_SIZE + 1));
				
		}
	}
}

void	better_pixel_put(t_img *img, int x, int y, int color)
{
	int offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}

void	create_img(t_img *img, void *mlx, int size, int color)
{
	//img = malloc(sizeof(t_img));
	img->img = mlx_new_image(mlx, size, size);
	img->pixel_ptr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);

	// si puo cambiare con il while
	for (int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			better_pixel_put(img, j, i, color);
		}
	}
	
}

int	main(int argc, char **argv)
{
	t_cubed		cubed;
	t_game		*game;
	t_img		*img;

	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	cubed.game = game;
	if (!parsing(argv, argc, &cubed))
		return (0);
	screen_setting(&cubed);
	img = malloc(sizeof(t_img));
	cubed.img = img;
	create_map();
	draw_map(&cubed, map);
	create_img(img, cubed.mlx, 8, 0x000000);
		
	//mlx_key_hook(cubed.window, &key_events, &cubed);
	mlx_put_image_to_window(cubed.mlx, cubed.window, cubed.img->img, PLAYER_X, PLAYER_Y);
	mlx_hook(cubed.window, 17, 1L << 17, &ft_close, &cubed);
	mlx_hook(cubed.window, 02, 1L << 0, &key_events, &cubed);
	// rendering();
	mlx_loop(cubed.mlx);
	return (0);
}*/
