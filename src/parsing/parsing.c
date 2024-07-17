/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/17 17:41:34 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	count_map_columns(int fd, t_cubed *cubed)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_error("Error: READ of file failed\n", cubed);
	}
	while (line)
	{
		// printf("line = '%c'\n", line[i]);
		// if (line[0] != '1' && line[0] != 'N' && line[0] != '\0'
		// 	&& line[0] != 'W' && line[0] != 'S' && line[0] != 'E'
		// 	&& line[0] != 'F' && line[0] != 'C' && line[0] != '\n')
		// {
		// 	close(fd);
		// 	ft_error("Error: invalid map\n", cubed);
		// }
		if (ft_strchr(line, '1'))
			cubed->game->ht += 1;
		free(line);
		line = get_next_line(fd);
	}
	printf("ht = %d\n", cubed->game->ht);
	free(line);
	get_next_line(-1);
	return (1);
}

// void	check_map(t_cubed *cubed)
// {
// 	int	i;
// 	int	h;
// 	int	c;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	h = cubed->game->ht;
// 	c = cubed->game->counter;
// 	// cubed->game->world_map[c] = ft_calloc(sizeof (char *), ft_strlen(line));
// 	while (line[++i])
// 	{
// 		if (c == 0 || c == h) // prima e ultima riga della mappa
// 		{
// 			if (line[i] == '1')
// 				continue;
// 				// cubed->game->world_map[c][++j] = line[i];
// 			else
// 				ft_error("Error: invalid map\n", cubed);
// 		}
// 		else // resto della mappa
// 		{
// 			if ((line[0] == '1' && i == 0) || (line[ft_strlen(line)] == '1'
// 				&& i == (int)ft_strlen(line))) // check per inizio e fine riga
// 				continue;
// 				// cubed->game->world_map[c][++j] = line[i];
// 			else
// 				ft_error("Error: invalid map\n", cubed);
// 			if (line[i] == '1')
// 				continue;
// 			else if (line[i] == '0' && cubed->game->world_map[c - 1][i] == '\n')
				
// 				// cubed->game->world_map[c][++j] = line[i];
// 		}
// 	}
// 	cubed->game->counter += 1;
// }

int	file_checker(int fd, t_cubed *cubed)
{
	char	*line;
	int		i;
	
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_error("Error: reading of file failed\n", cubed);
	}
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i, "WE", 2))
			textures_check(line + i, cubed);
		else if (line[i] == 'F' || line[i] == 'C')
			surfaces_check(line + i, cubed);
		else if (line[i])
		{
			line[ft_strlen(line) - 1] = '\0';
			cubed->game->world_map[cubed->game->counter++] = ft_strdup(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	get_next_line(-1);
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
				continue;
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
	close(fd);
	check_type(map);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
	{
		close(fd);
		ft_error("Error: opening file failed\n", cubed);
	}
	count_map_columns(fd, cubed);
	close(fd);
	cubed->game->world_map = ft_calloc(sizeof (char **), cubed->game->ht + 1);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
	{
		close(fd);
		ft_error("Error: opening file failed\n", cubed);
	}
	file_checker(fd, cubed);
	close(fd);
	return (0);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_error(USAGE, cubed), 0);
	cubed->game = malloc(sizeof (t_game));
	if (!cubed->game)
		return (ft_error("Error: allocation failed\n", 0));
	cubed->game->ht = 0;
	cubed->game->counter = 0;
	cubed->game->is_wall = 0;
	check_file(argv[1], cubed);
	print_matrix(cubed->game->world_map);
	// check_map(cubed);
	return (1);
}
