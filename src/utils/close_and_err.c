/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:10:47 by nromito           #+#    #+#             */
/*   Updated: 2024/07/18 19:44:47 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	close_fds(void)
{
	int	fd;

	fd = 0;
	while (fd < 1024)
		fd++;
}

int ft_error(char *error, t_cubed *cubed)
{
	ft_putendl_fd(error, 2);
	ft_close(cubed, 1);
	return (0);
}

int	free_game(t_cubed *cubed)
{
	if (cubed->game->ea)
		free (cubed->game->ea);
	if (cubed->game->no)
		free (cubed->game->no);
	if (cubed->game->so)
		free (cubed->game->so);
	if (cubed->game->we)
		free (cubed->game->we);
	free(cubed->game);
	return (1);
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
	free_game(cubed);
	//if (cubed->map)
	//	free_matrix(cubed->map);
	free(cubed->keys);
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free (cubed->mlx);
	}
	close_fds();
	exit (err_status);
}
