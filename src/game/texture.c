/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:36:45 by nromito           #+#    #+#             */
/*   Updated: 2024/07/26 16:25:29 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	load_texture(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (i == 0)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->no, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 1)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->so, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 2)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->we, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 3)
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->ea, &cubed->texture[i].w , &cubed->texture[i].h);
		else if (i == 4)
		{
			cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, "src/textures/pillar.xpm", &cubed->texture[i].w , &cubed->texture[i].h);
			printf("w = %d, h = %d\n", cubed->texture[i].w, cubed->texture[i].h);
		}
		else if (!cubed->texture[i].img)
			ft_error("Error: Failed to load xpm file\n", cubed);
		cubed->texture[i].data = (int *)mlx_get_data_addr(cubed->texture[i].img, &cubed->texture[i].bits_per_pixel, &cubed->texture[i].line_len, &cubed->texture[i].endian);
		i++;
	}
}
