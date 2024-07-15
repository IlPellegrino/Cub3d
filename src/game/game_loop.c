/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:14:33 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/15 17:31:58 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	game_loop(t_cubed *cubed)
{
	mlx_destroy_image(cubed->mlx, cubed->img);
	cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	// hook the player;
	//cast_rays(mlx);
	mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img, 0, 0);
	return (1);
}