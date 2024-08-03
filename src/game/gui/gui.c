/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:22:45 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 19:33:21 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

static void	draw_background(t_img *img)
{
	int	i;
	int	j;

	i = HEIGHT - 30;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			better_pixel_put(img, j, i, 0x000000);
	}
}

void	display_data(t_cubed *cubed)
{
	draw_background(cubed->img);
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
	x = WIDTH / 2 - CROSS_SIZE / 2;
	y = HEIGHT / 2 - 1;
	i = -1;
	while (++i < CROSS_SIZE)
	{
		j = -1;
		while (++j < 2)
			better_pixel_put(cubed->img, x + i, y + j, color);
	}
}

void	gui_2(t_cubed *cubed)
{
	mlx_string_put(cubed->mlx, cubed->win, 330, HEIGHT - 10, tea_green, "X: ");
	mlx_string_put(cubed->mlx, cubed->win, 410, HEIGHT - 10, tea_green, "Y: ");
	mlx_string_put(cubed->mlx, cubed->win, (WIDTH / 2) - 3,
		HEIGHT - 10, tea_green, "CUB3D");
	mlx_string_put(cubed->mlx, cubed->win, WIDTH - 120, HEIGHT - 10,
		tea_green, "@CIUSCA -- @NROMITO");
	mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 250, HEIGHT - 10,
		tea_green, "HEIGHT: ");
	mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 150, HEIGHT - 10,
		tea_green, "WIDTH: ");
}

void	str_gui(t_cubed *cubed)
{
	char	*str;

	str = ft_itoa(get_curr_time(cubed->time));
	mlx_string_put(cubed->mlx, cubed->win, 64, HEIGHT - 10, tea_green, str);
	mlx_string_put(cubed->mlx, cubed->win, 120, HEIGHT - 10,
		tea_green, "FOV: ");
	free(str);
	str = ft_itoa(cubed->settings->fov);
	mlx_string_put(cubed->mlx, cubed->win, 150, HEIGHT - 10, tea_green, str);
	free(str);
	str = ft_itoa(cubed->player->y);
	mlx_string_put(cubed->mlx, cubed->win, 430, HEIGHT - 10, tea_green, str);
	free(str);
	str = ft_itoa(cubed->player->x);
	mlx_string_put(cubed->mlx, cubed->win, 350, HEIGHT - 10, tea_green, str);
	free(str);
	str = ft_itoa(WIDTH);
	mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 200, HEIGHT - 10,
		tea_green, str);
	free(str);
	str = ft_itoa(HEIGHT);
	mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 300, HEIGHT - 10,
		tea_green, str);
	free(str);
}

void	text_gui(t_cubed *cubed)
{
	char	*mode;

	if (cubed->keys->shift)
		mode = "RUNNING";
	else
		mode = "WALKING";
	if (cubed->gui->open_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15,
			HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO OPEN DOOR");
	else if (cubed->gui->close_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15,
			HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO CLOSE DOOR");
	str_gui(cubed);
	mlx_string_put(cubed->mlx, cubed->win, 30, HEIGHT - 10,
		tea_green, "TIME: ");
	mlx_string_put(cubed->mlx, cubed->win, 210, HEIGHT - 10,
		tea_green, "MODE: ");
	mlx_string_put(cubed->mlx, cubed->win, 244, HEIGHT - 10, tea_green, mode);
	gui_2(cubed);
}
