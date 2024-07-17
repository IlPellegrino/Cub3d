/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:06:11 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 16:11:50 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_path(char *path)
{
	int	i;
	
	i = -1;
	while (path[++i])
	{
		if (path[i] == '.' && i != 0)
		{
			if (!ft_strncmp(path + i, ".xpm", 5))
				continue;
			else
				return (0);
		}
	}
	return (1);
}

int	assign_path(char *prefix, t_cubed *cubed, char *path)
{
	if (!ft_strncmp(prefix, "NO", 3))
		cubed->game->no = ft_strdup(path);
	else if (!ft_strncmp(prefix, "WE", 3))
		cubed->game->we = ft_strdup(path);
	else if (!ft_strncmp(prefix, "SO", 3))
		cubed->game->so = ft_strdup(path);
	else if (!ft_strncmp(prefix, "EA", 3))
		cubed->game->ea = ft_strdup(path);
	return (1);
}

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

int	check_colors(char *color, t_cubed *cubed, int surface)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;
	
	rgb = ft_split(color, ',');
	if (!rgb)
		ft_error("Error: allocation failed\n", cubed);
	rgb[2][ft_strlen(rgb[2] - 1)] = '\0'; 
	if (!is_digit(rgb) || matrix_len(rgb) > 3)
	{
		free_matrix(rgb);
		ft_error("Error: invalid color\n", cubed);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if ((r < 0 || r > 255) && (g < 0 || g > 255) && (b < 0 || b > 255))
	{
		free_matrix(rgb);
		ft_error("Error: invalid color\n", cubed);
	}
	if (surface == F)
		cubed->game->floor_cl = create_trgb(0, r, g, b);
	else if (surface == C)
		cubed->game->ceiling_cl = create_trgb(0, r, g, b);
	return (1);
}

int	surfaces_check(char *line, t_cubed *cubed)
{
	char	**colors;
	
	colors = ft_split(line, ' ');
	if (!colors)
		ft_error("Error: allocation failed\n", cubed);
	if (matrix_len(colors) > 2)
		ft_error("Error: wrong input\n", cubed);
	if (!ft_strncmp(colors[0], "F", 2))
		check_colors(colors[1], cubed, F);
	else if (!ft_strncmp(colors[0], "C", 2))
		check_colors(colors[1], cubed, C);
	else
		ft_error("Error: Wrong input\n", cubed);
	return (1);
}

int	textures_check(char *line, t_cubed *cubed)
{
	char	**splitted;
	int		fd;

	splitted = ft_split(line, ' ');
	if (!splitted)
		ft_error("Error: allocation failed\n", cubed);
	splitted[1][ft_strlen(splitted[1]) - 1] = '\0';
	fd = open(splitted[1], O_RDONLY);
	if (fd < 0)
		ft_error("Error: wrong path to file\n", cubed);
	if (!check_path(splitted[1]))
	{
		free_matrix(splitted);
		ft_error("Error: wrong path for walls\n", cubed);
	}
	assign_path(splitted[0], cubed, splitted[1]);
	close(fd);
	free_matrix(splitted);
	return (1);
}
