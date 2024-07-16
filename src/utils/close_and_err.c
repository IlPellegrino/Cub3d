/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:10:47 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 17:47:44 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int ft_error(char *error, t_cubed *cubed)
{
	ft_putendl_fd(error, 2);
	ft_close(cubed, 1);
	return (0);
}

int	ft_close(t_cubed *cubed, int err_status)
{
	if (cubed->img)
		mlx_destroy_image(cubed->mlx, cubed->img);
	if (cubed->win)
		mlx_destroy_window(cubed->mlx, cubed->win);
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free (cubed->mlx);
	}
	//free (cubed->raycast);
	if (cubed->game)
		free (cubed->game);
	exit (err_status);
}
