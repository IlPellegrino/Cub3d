/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/08/06 16:56:57 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"
#include <time.h>

int	main(int argc, char **argv)
{
	t_cubed	cubed;

	if (!parsing(argv, argc, &cubed))
		return (1);
	init_data(&cubed);
	load_texture(&cubed);
	time(&cubed.time);
	mlx_mouse_move(cubed.mlx, cubed.win, WIDTH / 2, HEIGHT / 2);
	mask_manager(&cubed);
	mlx_loop_hook(cubed.mlx, &game_loop, &cubed);
	mlx_loop(cubed.mlx);
}
