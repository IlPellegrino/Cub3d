/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/19 17:55:48 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

char	*get_next_line_check(t_cubed *cubed, char *line, int fd)
{
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_error("Error: reading of file failed\n", cubed);
	}
	return (line);
}

int	file_checker(int fd, t_cubed *cubed)
{
	char	*line;
	int		i;

	line = NULL;
	line = get_next_line_check(cubed, line, fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i, "WE", 2))
			textures_check(line + i, cubed, fd);
		else if (line[i] == 'F' || line[i] == 'C')
			surfaces_check(line + i, cubed, fd);
		else if (line[i] == '1')
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			cubed->map[cubed->game->counter++] = ft_strdup(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (1);
}

int	check_type(char *map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i] == '.' && i != 0)
		{
			if (!ft_strncmp(map + i, ".cub", 5))
				continue ;
			else
				return (0);
		}
	}
	return (1);
}

int	check_file(char *map, t_cubed *cubed)
{
	int		fd;

	fd = open(map, __O_DIRECTORY, 0677);
	if (fd > 0)
	{
		close(fd);
		ft_error("Error: Cub3d does not accept directories\n", cubed);
	}
	check_type(map);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
		ft_error("Error: Cub3D accepts only '.cub' files\n", cubed);
	count_map_columns(fd, cubed);
	if (fd)
		close (fd);
	cubed->map = ft_calloc(sizeof (char **), cubed->game->ht + 1);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
		ft_error("Error: Cub3D accepts only '.cub' files\n", cubed);
	file_checker(fd, cubed);
	if (fd)
		close(fd);
	return (0);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_error(USAGE, cubed), 0);
	check_file(argv[1], cubed);
	if (!cubed->game->no || !cubed->game->so
		|| !cubed->game->ea || !cubed->game->we)
		ft_error("Error: invalid texture direction\n", cubed);
	print_matrix(cubed->map);
	check_map(cubed); //TODO controllare parser per 0 1 della mappa alla fine e inizio
	count_width(cubed);
	return (1);
}
