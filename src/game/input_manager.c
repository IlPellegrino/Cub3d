/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/24 19:11:04 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"


int	check_move(t_cubed *cubed, t_keys *key)
{
	t_player		*p;
	int			    coll_len;
	double			dist;

	coll_len = 17;
	dist = ((PLAYER_SPEED + coll_len) * 0.1);
	p = cubed->player;
	if (key->w)
		move_up(cubed, coll_len);
	else if (key->s)
		move_down(cubed, coll_len);
	if (key->a)
		move_right(cubed, coll_len);
	else if (key->d)
		move_left(cubed, coll_len);
	return (1);
}


int	check_map_size(t_cubed *cubed)
{
	t_settings	*settings;
	t_keys		*key;
	int			i;

	i = 0;			
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

int	move_handler(t_cubed *cubed)
{
	t_keys	*key;

	key = cubed->keys;
	if (key->esc)
		ft_close(cubed, 0);
	check_move(cubed, key);
	rotate_player(cubed, key);
	// maybe move this function
	check_map_size(cubed);
	return (1);
}
