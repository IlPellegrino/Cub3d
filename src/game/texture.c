/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:36:45 by nromito           #+#    #+#             */
/*   Updated: 2024/07/31 19:15:36 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	load_door_animation(t_cubed *cubed, int curr)
{
	int		i;
	t_img	*door_anim;
	char	*door_frame;
	char	*temp;

	i = 0;
	door_anim = cubed->door_anim;
	while (i < FRAME_NUMBER)
	{
		door_anim[i].frame = i;
		door_frame = ft_strjoin("src/textures/door animation/frame_", ft_itoa(i + 1));
		temp = ft_strdup(door_frame);
		free(door_frame);
		door_frame = ft_strjoin(temp, ".xpm");
		free(temp);
		printf("door_frame: %s\n", door_frame);
		printf("door frame %s\n", door_frame);
		door_anim[i].img = mlx_xpm_file_to_image(cubed->mlx, door_frame, &door_anim[i].w , &door_anim[i].h);
		if (!door_anim[i].img)
			ft_error("Error: Failed to load xpm file\n", cubed);
		door_anim[i].data = (int *)mlx_get_data_addr(door_anim[i].img, &door_anim[i].bits_per_pixel, &door_anim[i].line_len, &door_anim[i].endian);
		free(door_frame);
		i++;
	}
	cubed->texture[curr] = door_anim[0];
}

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
			load_door_animation(cubed, i);
		}
		else if (!cubed->texture[i].img)
			ft_error("Error: Failed to load xpm file\n", cubed);
		cubed->texture[i].data = (int *)mlx_get_data_addr(cubed->texture[i].img, &cubed->texture[i].bits_per_pixel, &cubed->texture[i].line_len, &cubed->texture[i].endian);
		i++;
	}
}
