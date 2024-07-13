/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:10:47 by nromito           #+#    #+#             */
/*   Updated: 2024/07/12 12:24:51 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int ft_error(char *error, t_cubed *cubed)
{
	ft_putendl_fd(error, 2);
	ft_close(cubed);
	return (0);
}

int	ft_close(t_cubed *cubed)
{
	if (cubed->img)
		mlx_destroy_image(cubed->mlx, cubed->img);
	if (cubed->window)
		mlx_destroy_window(cubed->mlx, cubed->window);
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free (cubed->mlx);
	}
	free (cubed->raycast);
	free (cubed->game);
	exit (0);
}
