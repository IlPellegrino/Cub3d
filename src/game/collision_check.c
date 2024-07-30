/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:58:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/30 18:18:02 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_wall(t_cubed *cubed, double x, double y)
{
	int			i;
	int			j;
	
	j = (int)(x / TILE_SIZE);
	i = (int)(y / TILE_SIZE);
	if (i < 0 || i >= cubed->game->ht || j < 0 || j >= cubed->game->wd)
		return (1);
	if (cubed->map[i][j] == '1' || cubed->map[i][j] == 'D')
		return (1);
	return (0);
}

int	validate_position(t_cubed *cubed, double dist, double dir)
{
	t_player	*p;
	double		new_dist;
	double		new_angle;

	new_dist = dist;
	p = cubed->player;
	if (dir == NORTH)
		new_angle = p->angle;
	else if (dir == SOUTH)
		new_angle = p->angle + PI;
	else if (dir == WEST)
		new_angle = p->angle + PI / 2;
	else
		new_angle = p->angle - PI / 2;
	if (new_angle > 2 * PI)
		new_angle -= 2 * PI;
	if (dir != NORTH && dir != SOUTH)
		new_dist = 6;
	if (is_wall(cubed, p->x + cos(new_angle) * new_dist, p->y + sin(new_angle) * new_dist)
	|| is_wall(cubed, p->x + cos(new_angle + 0.1) * new_dist, p->y + sin(new_angle + 0.1) * new_dist)
	|| is_wall(cubed, p->x + cos(new_angle - 0.1) * new_dist, p->y + sin(new_angle - 0.1) * new_dist))
		return (0);
	return (1);
}
