/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:03:36 by nromito           #+#    #+#             */
/*   Updated: 2024/08/06 17:04:03 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_texture(t_cubed *cubed, int i, int k)
{
	return (!ft_strncmp(cubed->game->cub[i] + k, "NO", 2)
		|| !ft_strncmp(cubed->game->cub[i] + k, "SO", 2)
		|| !ft_strncmp(cubed->game->cub[i] + k, "EA", 2)
		|| !ft_strncmp(cubed->game->cub[i] + k, "WE", 2));
}
