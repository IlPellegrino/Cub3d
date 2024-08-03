/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:10:47 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 19:37:57 by ciusca           ###   ########.fr       */
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

int	ft_error(char *error, t_cubed *cubed)
{
	ft_putendl_fd(error, 2);
	ft_close(cubed, 1);
	return (0);
}

int	free_texture(t_cubed *cubed)
{
	mlx_destroy_image(cubed->mlx, cubed->texture[0].img);
	mlx_destroy_image(cubed->mlx, cubed->texture[1].img);
	mlx_destroy_image(cubed->mlx, cubed->texture[2].img);
	mlx_destroy_image(cubed->mlx, cubed->texture[3].img);
	mlx_destroy_image(cubed->mlx, cubed->texture[4].img);
	return (1);
}

int	free_game_texture(t_cubed *cubed)
{
	if (cubed->game->cub)
		free_matrix(cubed->game->cub);
	if (cubed->game->ea)
		free (cubed->game->ea);
	if (cubed->game->no)
		free (cubed->game->no);
	if (cubed->game->so)
		free (cubed->game->so);
	if (cubed->game->we)
		free (cubed->game->we);
	free_texture(cubed);
	free(cubed->game);
	return (1);
}

int	ft_close(t_cubed *cubed, int err_status)
{
	if (cubed->img)
		mlx_destroy_image(cubed->mlx, cubed->img->img);
	if (cubed->win)
		mlx_destroy_window(cubed->mlx, cubed->win);
	if (cubed->raycast)
		free (cubed->raycast);
	if (cubed->player)
		free (cubed->player);
	free_game_texture(cubed);
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free(cubed->mlx);
	}
	//free (cubed->img);
	if (cubed->map)
	{
		free_matrix(cubed->map);
		cubed->map = NULL;
	}
	free(cubed->keys);
	free(cubed->gui);
	free(cubed->settings);
	close_fds();
	exit (err_status);
}
