/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:03:01 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 00:35:05 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

void	move_up(t_cubed *cubed, double dist)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = cubed->player;
	new_x = p->x + p->d_x * (PLAYER_SPEED * 0.1);
	new_y = p->y + p->d_y * (PLAYER_SPEED * 0.1);
	if (validate_position(cubed, dist, NORTH))
	{
		p->x = new_x;
		p->y = new_y;
	}
}

void	move_down(t_cubed *cubed, double dist)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = cubed->player;
	new_x = p->x - p->d_x * (PLAYER_SPEED * 0.1);
	new_y = p->y - p->d_y * (PLAYER_SPEED * 0.1);
	if (validate_position(cubed, dist, SOUTH))
	{
		p->x = new_x;
		p->y = new_y;
	}
}

void	move_left(t_cubed *cubed, double dist)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = cubed->player;
	new_x = p->x - p->d_y * (PLAYER_SPEED * 0.1);
	new_y = p->y + p->d_x * (PLAYER_SPEED * 0.1);
	if (validate_position(cubed, dist, WEST))
	{
		p->x = new_x;
		p->y = new_y;
	}
}

void	move_right(t_cubed *cubed, double dist)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = cubed->player;
	new_x = p->x + p->d_y * (PLAYER_SPEED * 0.1);
	new_y = p->y - p->d_x * (PLAYER_SPEED * 0.1);
	if (validate_position(cubed, dist, EAST))
	{
		p->x = new_x;
		p->y = new_y;
	}
}

int	rotate_player(t_cubed *cubed, t_keys *key)
{
	t_player	*p;

	p = cubed->player;
	if (key->left)
	{
		p->angle -= (ROTATION_SPEED * 0.01);
		if (p->angle < 0)
			p->angle += 2 * PI;
		p->d_x = cos(p->angle);
		p->d_y = sin(p->angle);
	}
	if (key->right)
	{
		p->angle += (ROTATION_SPEED * 0.01);
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
		p->d_x = cos(p->angle);
		p->d_y = sin(p->angle);
	}
	return (1);
}
