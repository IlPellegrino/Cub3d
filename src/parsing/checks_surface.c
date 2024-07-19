/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:48:53 by nromito           #+#    #+#             */
/*   Updated: 2024/07/19 16:07:05 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_texture_error(t_cubed *cubed, char **splitted, int file)
{
	if (!splitted || matrix_len(splitted) != 2)
	{
		close(file);
		if (splitted)
			free_matrix(splitted);
		ft_error("Error: wrong texture syntax\n", cubed);
	}
	return (1);
}

int	check_path(char *path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		if (path[i] == '.' && i != 0)
		{
			if (!ft_strncmp(path + i, ".xpm", 5))
				continue ;
			else
				return (0);
		}
	}
	return (1);
}

int	assign_path(char *prefix, t_cubed *cubed, char *path)
{
	if (!ft_strncmp(prefix, "NO", 3) && !cubed->game->no)
		cubed->game->no = ft_strdup(path);
	else if (!ft_strncmp(prefix, "WE", 3) && !cubed->game->we)
		cubed->game->we = ft_strdup(path);
	else if (!ft_strncmp(prefix, "SO", 3) && !cubed->game->so)
		cubed->game->so = ft_strdup(path);
	else if (!ft_strncmp(prefix, "EA", 3) && !cubed->game->ea)
		cubed->game->ea = ft_strdup(path);
	else
		ft_error("Error: texture duplicates not allowed\n", cubed);
	return (1);
}

int	surfaces_check(char *line, t_cubed *cubed, int file)
{
	char	**colors;

	colors = ft_split(line, ' ');
	if (!colors || matrix_len(colors) != 2)
	{
		if (colors)
			free_matrix(colors);
		close(file);
		free(line);
		ft_error("Error: invalid color\n", cubed);
	}
	if (!ft_strncmp(colors[0], "F", 2))
		check_colors(colors, cubed, F, file);
	else if (!ft_strncmp(colors[0], "C", 2))
		check_colors(colors, cubed, C, file);
	else
	{
		close(file);
		free_matrix(colors);
		ft_error("Error: invalid color\n", cubed);
	}
	return (1);
}

int	textures_check(char *line, t_cubed *cubed, int file)
{
	char	**splitted;
	int		h;
	int		fd;

	splitted = ft_split(line, ' ');
	check_texture_error(cubed, splitted, file);
	h = matrix_len(splitted) - 1;
	splitted[h][ft_strlen(splitted[h]) - 1] = '\0';
	fd = open(splitted[1], O_RDONLY);
	if (fd < 0)
	{
		free(line);
		free_matrix(splitted);
		ft_error("Error: wrong path to file\n", cubed);
	}
	close(fd);
	if (!check_path(splitted[1]))
	{
		free(line);
		free_matrix(splitted);
		ft_error("Error: wrong path for walls\n", cubed);
	}
	assign_path(splitted[0], cubed, splitted[1]);
	free_matrix(splitted);
	return (1);
}
