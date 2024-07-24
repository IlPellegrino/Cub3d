/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:58:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/24 18:47:12 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_wall(t_cubed *cubed, double x, double y)
{
	int			i;
	int			j;

	j = (int)(x / TILE_SIZE);
	i = (int)(y / TILE_SIZE);
	if (cubed->map[i][j] == '1' || cubed->map[i][j] == 'D')
		return (1);
	return (0);
}

int	validate_position(t_cubed *cubed, double new_x, double new_y)
{
	t_player	*player;

	player = cubed->player;
	return (!is_wall(cubed, new_x, new_y));
}