/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/25 20:48:25 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int mouse_rotate_pov(t_cubed *cubed)
{
    t_player    *p;
    int         x, y;
    int         center_x, delta_x;
    double      rotation;

	x = cubed->game->mouse_x;
	y = cubed->game->mouse_y;
    p = cubed->player;
    center_x = WIDTH / 2;
    //mlx_mouse_get_pos(cubed->mlx, cubed->win, &x, &y); // Get current mouse position
    delta_x = x - center_x; // Calculate the difference from the center

    if (abs(delta_x) > 2) // To prevent jitter, ignore very small movements
    {
        rotation = delta_x * SENSITIVITY;
        p->angle += rotation;

        // Ensure the angle stays within [0, 2*PI]
        if (p->angle > 2 * PI)
            p->angle -= 2 * PI;
        else if (p->angle < 0)
            p->angle += 2 * PI;

        // Update direction vectors
        p->d_x = cos(p->angle);
        p->d_y = sin(p->angle);

        // Reset mouse position to the center
        mlx_mouse_move(cubed->mlx, cubed->win, center_x, HEIGHT / 2);
    }

    return (1);
}

int	move_player(t_cubed *cubed, t_keys *key)
{
	t_player		*p;
	int			    coll_len;
	double			dist;

	coll_len = 17;
	dist = ((PLAYER_SPEED + coll_len) * 0.1);
	p = cubed->player;
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
	mlx_mouse_get_pos(cubed->mlx, cubed->win, &cubed->game->mouse_x, &cubed->game->mouse_y);
	mouse_rotate_pov(cubed);
	move_player(cubed, key);
	rotate_player(cubed, key);
	// maybe move this function
	check_map_size(cubed);
	return (1);
}
