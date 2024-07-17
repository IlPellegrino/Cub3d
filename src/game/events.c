/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 16:42:35 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	mid_point(int point)
{
	point += PLAYER_SIZE / 2;
	return (point);
}

int	events(int key, t_cubed *cubed)
{
	t_player	*p;

	p = cubed->player;
	printf("key = %d\n", key);
	if (key == esc)
		ft_close(cubed, 0);
	else if (key == w && !is_wall(cubed, p->x, p->y - PLAYER_SPEED))
		p->y -= PLAYER_SPEED;
	else if (key == s && !is_wall(cubed, p->x, (p->y + PLAYER_SIZE - 1) + PLAYER_SPEED))
		p->y += PLAYER_SPEED;
	else if (key == a && !is_wall(cubed, p->x - PLAYER_SPEED, p->y))
		p->x -= PLAYER_SPEED;
	else if (key == d && !is_wall(cubed, (p->x + PLAYER_SIZE - 1) + PLAYER_SPEED, p->y))
		p->x += PLAYER_SPEED;
	//draw_map(cubed, cubed->map);
	//draw_player(cubed, p->x, p->y);
	//draw_line(cubed->mlx, cubed->win, mid_point(p->x), mid_point(p->y), 300, 240, 0x00FF00);
	return (1);
}
