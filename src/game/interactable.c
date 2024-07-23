/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:11:16 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/23 14:23:42 by ciusca           ###   ########.fr       */
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
	i = (int)((p->y + p->d_y * 20) / TILE_SIZE);
	j = (int)((p->x + p->d_x * 20) / TILE_SIZE);
	printf("d_x = %f, d_y = %f\n", p->d_x, p->d_y);
	printf("i = %d, j = %d\n", i, j);
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