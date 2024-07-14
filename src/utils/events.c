/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 00:21:05 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	can_move(int x, int y)//, char **map)
{
	if (x + 5 > WIDTH || y + 5 > HEIGHT
		|| x - 5 < 0 || y - 5 < 0) /*||
		map[y][x + 5] == '1' || map[y + 5][x] == '1'
		|| map[y][x - 5] == '1' || map[y - 5][x] == '1')*/
		return (0);
	return (1);
}

int	key_events (int key, t_cubed *cubed)
{
	//mlx_do_key_autorepeatoff(cubed->mlx);
	//mlx_do_key_autorepeaton(cubed->mlx);
	t_img *del;
	
	del = malloc(sizeof(t_img));
	create_img(del, cubed->mlx, 8, 0x00000);
	mlx_put_image_to_window(cubed->mlx, cubed->window, del->img, cubed->x_player, cubed->y_player);
	printf("player x = %d\nplayer y = %d\n", cubed->x_player, cubed->y_player);
	if (key == w && can_move(cubed->x_player, cubed->y_player))
		cubed->y_player -= 5;
	else if (key == a && can_move(cubed->x_player, cubed->y_player))
		cubed->x_player -= 5;
	else if (key == d && can_move(cubed->x_player, cubed->y_player))
		cubed->x_player += 5;
	else if (key == s && can_move(cubed->x_player, cubed->y_player))
		cubed->y_player += 5;
	else if (key == esc)
		ft_close(cubed, 0);
	mlx_put_image_to_window(cubed->mlx, cubed->window, cubed->img->img, cubed->x_player, cubed->y_player);
	return (1);
}
