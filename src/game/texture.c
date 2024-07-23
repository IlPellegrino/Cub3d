/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:36:45 by nromito           #+#    #+#             */
/*   Updated: 2024/07/23 10:41:42 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	load_texture(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cubed->texture[i].img = mlx_xpm_file_to_image(cubed->mlx, cubed->game->no, &cubed->texture[i].w , &cubed->texture[i].h);
		if (!cubed->texture[i].img)
			ft_error("Error: Failed to load xpm file\n", cubed);
		cubed->texture[i].data = (int *)mlx_get_data_addr(cubed->texture[i].img, &cubed->texture[i].bits_per_pixel, &cubed->texture[i].line_len, &cubed->texture[i].endian);
		i++;
	}
}

int	get_texture(t_cubed *cubed)
{
	t_img	*text;
	int	color;
	int	y;
	int	x;

	y = -1;
	text = cubed->texture;
	while (++y < cubed->texture[0].h)
	{
		x = -1;
		while (++x < cubed->texture[0].w)
		{
			color = text[0].data[y * cubed->texture[0].w + x];
            // printf("Pixel at (%d, %d) has color: %#x\n", x, y, color);
		}
	}
	return (color);
}