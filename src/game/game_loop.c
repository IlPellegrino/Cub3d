/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/26 17:27:58 by ciusca           ###   ########.fr       */
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

int blend_color(t_cubed *cubed, int x, int y, int color, float alpha)
{
    unsigned long bg_color;
    int red, green, blue;
    
    // Clamp alpha to the range [0, 1]
    if (alpha < 0.0) alpha = 0.0;
    if (alpha > 1.0) alpha = 1.0;

    // Get the background color
    bg_color = get_color(cubed->img, x, y);

    // Extract RGB components from the input color
    int input_red = ((color >> 16) & 0xFF);
    int input_green = ((color >> 8) & 0xFF);
    int input_blue = (color & 0xFF);

    // Extract RGB components from the background color
    int bg_red = ((bg_color >> 16) & 0xFF);
    int bg_green = ((bg_color >> 8) & 0xFF);
    int bg_blue = (bg_color & 0xFF);

    // Perform the blending based on the alpha value
    red = (int)((input_red * alpha) + (bg_red * (1 - alpha)));
    green = (int)((input_green * alpha) + (bg_green * (1 - alpha)));
    blue = (int)((input_blue * alpha) + (bg_blue * (1 - alpha)));

    // Return the blended color
    return ((red << 16) | (green << 8) | blue);
}

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
				color = blend_color(cubed, j, i, eggplant, 0.9);
			else if (x < 0 || y < 0 || y >= matrix_len(map) || x >= (int)ft_strlen(map[y]))
				color = blend_color(cubed, j, i, claret, 0.9);
			else if (map[y][x] == '1')
				color = blend_color(cubed, j, i, lion, 0.9);
			else if (map[y][x] == 'D')
				color = blend_color(cubed, j, i, purple, 0.9);
			else if (map[y][x] == 'C')
				color = blend_color(cubed, j, i, green, 0.9);
			else
				color = blend_color(cubed, j, i, snow, 0.9);
			better_pixel_put(img, j, i, color);
		}
	}
	
}

void	minimap(t_cubed *cubed, char **map)
{
	double		x_len;
	double		y_len;

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

int	pause_game(t_cubed *cubed)
{
	if (cubed->keys->pause)
	{
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 - 50, HEIGHT / 2, white, "PAUSE");
		return (0);
	}
	return (1);
}

int	game_loop(t_cubed *cubed)
{
	t_img		*img;
	img = cubed->img;
	if (!pause_game(cubed))
		return (0);
	//mlx_destroy_image(cubed->mlx, cubed->img->img);
	//create_img(cubed->mlx, cubed->img);
	text_gui(cubed);
	move_handler(cubed);
	rendering(cubed);
	interactable(cubed);
	minimap(cubed, cubed->map);
	draw_crosshair(cubed);
	text_gui(cubed);
	mlx_put_image_to_window(cubed->mlx, cubed->win, img->img, 0, 0);
	return (1);
}
