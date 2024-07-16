/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/16 20:32:38 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	events(int key, t_cubed *cubed)
{
	t_player	*p;

	p = cubed->player;
	printf("key = %d\n", key);
	if (key == esc)
		ft_close(cubed, 0);
	else if (key == w)
		p->y -= PLAYER_SPEED;
	else if (key == s)
		p->y += PLAYER_SPEED;
	else if (key == a)
		p->x -= PLAYER_SPEED;
	else if (key == d)
		p->x += PLAYER_SPEED;
	draw_map(cubed, cubed->map);
	draw_player(cubed, p->x, p->y);
	return (1);
}
