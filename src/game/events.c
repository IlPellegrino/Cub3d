/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 20:29:12 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	mid_point(int point)
{
	point += PLAYER_SIZE / 2;
	return (point);
}

int	check_rotate(t_cubed *cubed, int key)
{
	t_player	*p;

	p = cubed->player;
	if (key == left)
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * PI;
		p->d_x = cos(p->angle) * 20;
		p->d_y = sin(p->angle) * 20;
	}
	else if (key == right)
	{
		p->angle += 0.1;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
		p->d_x = cos(p->angle) * 20;
		p->d_y = sin(p->angle) * 20;
	}
	return (1);
}

int	check_move(t_cubed *cubed, int key)
{
	t_player	*p;

	p = cubed->player;
	if (key == w && !is_wall(cubed, p->x, (p->y - PLAYER_SIZE / 2) - PLAYER_SPEED))
		p->y -= PLAYER_SPEED;
	else if (key == s && !is_wall(cubed, p->x, (p->y + PLAYER_SIZE / 2) + PLAYER_SPEED))
		p->y += PLAYER_SPEED;
	else if (key == a && !is_wall(cubed,(p->x - PLAYER_SIZE / 2) - PLAYER_SPEED, p->y))
		p->x -= PLAYER_SPEED;
	else if (key == d && !is_wall(cubed, (p->x + PLAYER_SIZE / 2) + PLAYER_SPEED, p->y))
		p->x += PLAYER_SPEED;
	else
		return (0);
	return (1);
}

int	events(int key, t_cubed *cubed)
{
	printf("key = %d\n", key);
	if (key == esc)
		ft_close(cubed, 0);
	check_move(cubed, key);
	check_rotate(cubed, key);
	return (1);
}
