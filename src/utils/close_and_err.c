/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:10:47 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 15:38:31 by ciusca           ###   ########.fr       */
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
		mlx_destroy_image(cubed->mlx, cubed->img->img);
	free (cubed->img);
	if (cubed->win)
		mlx_destroy_window(cubed->mlx, cubed->win);
	free (cubed->raycast);
	free (cubed->player);
	free (cubed->game);
	free_matrix(cubed->map);
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free (cubed->mlx);
	}
	exit (err_status);
}
