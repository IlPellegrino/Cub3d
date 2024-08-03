/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:17:14 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 17:21:09 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

void	change_fov(t_cubed *cubed)
{
	t_settings	*settings;
	t_keys		*key;

	settings = cubed->settings;
	key = cubed->keys;
	if (key->page_up)
	{
		if (settings->fov < 90)
			settings->fov++;
	}
	else if (key->page_down)
	{
		if (settings->fov > 50)
			settings->fov--;
	}
	settings->radians_fov = settings->fov * PI / 180;
}

void	player_run(t_cubed *cubed)
{
	t_settings	*settings;
	t_keys		*key;

	key = cubed->keys;
	settings = cubed->settings;
	if (key->shift)
		settings->player_speed = PLAYER_SPEED * 3;
	else
		settings->player_speed = PLAYER_SPEED;
}

int	mouse_rotate_pov(t_cubed *cubed)
{
	t_player	*p;
	int			x;
	double		rotation;

	p = cubed->player;
	x = cubed->game->mouse_x;
	rotation = (x - (WIDTH / 2)) * SENSITIVITY * 0.001;
	p->angle += rotation;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
	p->d_x = cos(p->angle);
	p->d_y = sin(p->angle);
	if (x != WIDTH / 2)
		mlx_mouse_move(cubed->mlx, cubed->win, WIDTH / 2, HEIGHT / 2);
	return (1);
}

int	check_map_size(t_cubed *cubed)
{
	t_settings	*settings;
	t_keys		*key;

	settings = cubed->settings;
	key = cubed->keys;
	if (key->plus == 1)
	{
		if (settings->mini_size < 64)
			settings->mini_size++;
	}
	else if (key->minus == 1)
	{
		if (settings->mini_size > 10)
			settings->mini_size--;
	}
	return (1);
}