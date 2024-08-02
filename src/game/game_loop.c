/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/02 15:01:59 by ciusca           ###   ########.fr       */
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
