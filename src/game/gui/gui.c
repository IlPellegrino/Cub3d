/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:22:45 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/02 16:14:00 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

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

void	text_gui(t_cubed *cubed)
{
	if (cubed->gui->open_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15, HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO OPEN DOOR");
	else if (cubed->gui->close_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15, HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO CLOSE DOOR");

}