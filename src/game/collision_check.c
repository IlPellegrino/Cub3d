/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:58:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/05 15:53:06 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_wall(t_cubed *cubed, double x, double y)
{
	int	i;
	int	j;

	j = (int)(x / TILE_SIZE);
	i = (int)(y / TILE_SIZE);
	if (i < 0 || i >= cubed->game->ht || j < 0 || j >= cubed->game->wd)
		return (1);
	if (cubed->map[i][j] == '1' || cubed->map[i][j] == 'D')
		return (1);
	return (0);
}

int	validate_position(t_cubed *cub, double dist, double dir)
{
	t_player	*p;
	double		ndst;
	double		ang;

	ndst = dist;
	p = cub->player;
	if (dir == PI / 2)
		ang = p->angle;
	else if (dir == 3 * PI / 2)
		ang = p->angle + PI;
	else if (dir == WEST)
		ang = p->angle + PI / 2;
	else
		ang = p->angle - PI / 2;
	if (ang > 2 * PI)
		ang -= 2 * PI;
	if (dir != PI / 2 && dir != 3 * PI / 2)
		ndst = 10;
	if (is_wall(cub, p->x + cos(ang) * ndst, p->y + sin(ang) * ndst)
		|| is_wall(cub, p->x + cos(ang + 0.5) * ndst,
			p->y + sin(ang + 0.5) * ndst)
		|| is_wall(cub, p->x + cos(ang - 0.5) * ndst,
			p->y + sin(ang - 0.5) * ndst))
		return (0);
	return (1);
}
