/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:06:11 by nromito           #+#    #+#             */
/*   Updated: 2024/07/18 19:35:23 by nromito          ###   ########.fr       */
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

int	check_colors(char **color, t_cubed *cubed, int surface, int file)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;
	
	rgb = ft_split(color[1], ',');
	free_matrix(color);
	rgb[matrix_len(rgb) - 1][ft_strlen(rgb[matrix_len(rgb) - 1]) - 1] = '\0';
	if (!rgb || !is_digit(rgb) || matrix_len(rgb) != 3)
	{
		close(file);
		print_matrix(rgb);
		free_matrix(rgb);
		ft_error("Error: invalid color\n", cubed);
	}
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

int	surfaces_check(char *line, t_cubed *cubed, int file)
{
	char	**colors;
	
	colors = ft_split(line, ' ');
	if (!colors || matrix_len(colors) != 2)
	{
		if (colors)
			free_matrix(colors);
		close(file);
		while (line)
		{
			free(line);
			line = get_next_line(file);
		}
		get_next_line(-1);
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
	int		fd;

	splitted = ft_split(line, ' ');
	if (!splitted || matrix_len(splitted) != 2)
	{
		close(file);
		while (line)
		{
			free(line);
			line = get_next_line(file);
		}
		if (splitted)
			free_matrix(splitted);
		ft_error("Error: wrong texture syntax\n", cubed);
	}
	splitted[matrix_len(splitted) - 1][ft_strlen(splitted[matrix_len(splitted) - 1]) - 1] = '\0';
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
