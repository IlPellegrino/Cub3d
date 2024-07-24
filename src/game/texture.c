/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:36:45 by nromito           #+#    #+#             */
/*   Updated: 2024/07/24 11:05:20 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	load_texture(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->no, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 1)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->so, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 2)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->we, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 3)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->ea, &cubed->texture[i].w , &cubed->texture[i].h);
		if (!cubed->texture[i].img)
			ft_error("Error: Failed to load xpm file\n", cubed);
		cubed->texture[i].data = (int *)mlx_get_data_addr(cubed->texture[i].img, &cubed->texture[i].bits_per_pixel, &cubed->texture[i].line_len, &cubed->texture[i].endian);
		i++;
	}
}
