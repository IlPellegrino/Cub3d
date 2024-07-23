/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/23 16:56:12 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"


int	check_rotate(t_cubed *cubed, t_keys *key)
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
	else if (key->right)
	{
		p->angle += (ROTATION_SPEED * 0.01);
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
		p->d_x = cos(p->angle);
		p->d_y = sin(p->angle);
	}
	return (1);
}


int	check_move(t_cubed *cubed, t_keys *key)
{
	t_player		*p;
	double			new_x;
	double			new_y;

	p = cubed->player;
	if (key->w)
	{
		new_x = p->x + p->d_x * (PLAYER_SPEED * 0.1);
		new_y = p->y + p->d_y * (PLAYER_SPEED * 0.1);
		validate_position(cubed, new_x, new_y);
	}
	if (key->s)
	{
		new_x = p->x - p->d_x * ((PLAYER_SPEED) * 0.1);
		new_y = p->y - p->d_y * ((PLAYER_SPEED) * 0.1);
		validate_position(cubed, new_x, new_y);
	}
	if (key->a)
	{
		new_x = p->x + p->d_y * ((PLAYER_SPEED )* 0.1);
		new_y = p->y - p->d_x * ((PLAYER_SPEED )* 0.1);
		validate_position(cubed, new_x, new_y);
	}
	if (key->d)
	{
		new_x = p->x - p->d_y * ((PLAYER_SPEED )* 0.1);
		new_y = p->y + p->d_x * ((PLAYER_SPEED )* 0.1);
		validate_position(cubed, new_x, new_y);
	}
	return (1);
}

int	key_release(int realesed, t_keys *key)
{
	if (realesed == w)
		key->w = 0;
	else if (realesed == s)
		key->s = 0;
	else if (realesed == a)
		key->a = 0;
	else if (realesed == d)
		key->d = 0;
	else if (realesed == left)
		key->left = 0;
	else if (realesed == right)
		key->right = 0;
	else if (key->esc)
		key->esc = 0;
	//printf("release\n");
	return (1);
}

int	key_press(int pressed, t_keys *key)
{
	if (pressed == w)
		key->w = 1;
	else if (pressed == s)
		key->s = 1;
	else if (pressed == a)
		key->a = 1;
	else if (pressed == d)
		key->d = 1;
	else if (pressed == left)
		key->left = 1;
	else if (pressed == right)
		key->right = 1;
	else if (pressed == esc)
		key->esc = 1;
	else if (pressed == p && key->pause == 0)
		key->pause = 1;
	else if (pressed == p && key->pause == 1)
		key->pause = 0;
	else if (pressed == space)
		key->space = 1;
	return (0);
	//printf("press\n");
}

int	move_handler(t_cubed *cubed)
{
	t_keys	*key;

	key = cubed->keys;
	if (key->esc)
		ft_close(cubed, 0);
	check_move(cubed, key);
	check_rotate(cubed, key);
	//game_loop(cubed);
	return (1);
}
