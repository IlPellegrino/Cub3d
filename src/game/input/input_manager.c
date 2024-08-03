/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 17:19:57 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

int	move_player(t_cubed *cubed, t_keys *key)
{
	int	coll_len;

	coll_len = 20;
	if (key->w)
		move_up(cubed, coll_len);
	if (key->s)
		move_down(cubed, coll_len);
	if (key->a)
		move_right(cubed, coll_len);
	if (key->d)
		move_left(cubed, coll_len);
	return (1);
}


int	settings_handler(t_cubed *cubed)
{
	t_keys	*key;

	key = cubed->keys;
	if (key->esc)
		ft_close(cubed, 0);
	mlx_mouse_get_pos(cubed->mlx, cubed->win,
		&cubed->game->mouse_x, &cubed->game->mouse_y);
	mouse_rotate_pov(cubed);
	move_player(cubed, key);
	rotate_player(cubed, key);
	check_map_size(cubed);
	player_run(cubed);
	change_fov(cubed);
	return (1);
}
