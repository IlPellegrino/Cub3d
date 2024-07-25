/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:11:16 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/24 14:31:59 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	player_in_door(int player_x, int player_y, char **map)
{
	int	i;
	int	j;

	i = (player_y / TILE_SIZE);
	j = (player_x / TILE_SIZE);
	if (map[i][j] == 'C')
		return (1);
	return (0);
}

void	interactable(t_cubed *cubed)
{
	t_player	*p;
	int			i;
	int			j;

	p = cubed->player;
	i = (int)((p->y + p->d_y * 60) / TILE_SIZE);
	j = (int)((p->x + p->d_x * 60) / TILE_SIZE);
	if (cubed->map[i][j] == 'D' && cubed->keys->space)
	{
		cubed->map[i][j] = 'C';
	}
	else if (cubed->map[i][j] == 'C' && cubed->keys->space && !player_in_door(p->x, p->y, cubed->map))
	{
		cubed->map[i][j] = 'D';
	}
	cubed->keys->space = 0;
}