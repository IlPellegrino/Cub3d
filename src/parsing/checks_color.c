/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:06:11 by nromito           #+#    #+#             */
/*   Updated: 2024/07/24 17:35:28 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_digit(char **rgb)
{
	int	i;
	int	j;

	i = -1;
	while (rgb[++i])
	{
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (0);
		}
	}
	return (1);
}

int	check_error_color(t_cubed *cubed, char **rgb)
{
	if (!rgb || !is_digit(rgb) || matrix_len(rgb) != 3
		|| !rgb[2][0])
	{
		free_matrix(rgb);
		ft_error("Error: invalid color\n", cubed);
	}
	return (1);
}

int	check_colors(char **color, t_cubed *cubed, int surface)
{
	int		r;
	int		g;
	int		b;
	int		h;
	char	**rgb;

	rgb = ft_split(color[1], ',');
	free_matrix(color);
	h = matrix_len(rgb) - 1;
	if (rgb)
		rgb[h][ft_strlen(rgb[h]) - 1] = 0;
	check_error_color(cubed, rgb);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_matrix(rgb);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_error("Error: invalid color\n", cubed);
	if (surface == F && !cubed->game->floor_cl)
		cubed->game->floor_cl = create_trgb(0, r, g, b);
	else if (surface == C && !cubed->game->ceiling_cl)
		cubed->game->ceiling_cl = create_trgb(0, r, g, b);
	else
		ft_error("Error: no duplicates allowed\n", cubed);
	return (1);
}
