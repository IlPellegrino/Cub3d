/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/06 12:03:17 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	pause_game(t_cubed *cubed)
{
	if (cubed->keys->pause)
	{
		mlx_string_put(cubed->mlx, cubed->win,
			WIDTH / 2 - 50, HEIGHT / 2, white, "PAUSE");
		return (0);
	}
	return (1);
}

int	game_loop(t_cubed *cubed)
{
	t_img		*img;

	img = cubed->img;
	if (!pause_game(cubed))
		return (0);
	//text_gui(cubed);
	settings_handler(cubed);
	rendering(cubed);
	// printf("mand loop\n");
	mlx_put_image_to_window(cubed->mlx, cubed->win, img->img, 0, 0);
	return (1);
}
