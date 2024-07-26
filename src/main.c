/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/26 11:36:03 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

//                                  111
//problema quando nella mappa si ha 101
//                                  110
int	mouse_move(t_cubed *cubed)
{
	(void)cubed;
	return (1);
}

void	mask_manager(t_cubed *cubed)
{
	mlx_hook(cubed->win, KeyPress, KeyPressMask, &key_press, cubed->keys);
	mlx_hook(cubed->win, KeyRelease, KeyReleaseMask, &key_release, cubed->keys);
	mlx_hook(cubed->win, DestroyNotify, StructureNotifyMask, &ft_close, &cubed);
}

int	main(int argc, char **argv)
{
	t_cubed	cubed;

	if (!parsing(argv, argc, &cubed))
		return (1);
	init_data(&cubed);
	mlx_mouse_hide(cubed.mlx, cubed.win);	
	load_texture(&cubed);
	mask_manager(&cubed);
	mlx_loop_hook(cubed.mlx, &game_loop, &cubed);
	mlx_loop(cubed.mlx);
}
