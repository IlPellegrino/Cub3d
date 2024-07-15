/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 17:45:10 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	textures_check(char *line, t_cubed *cubed)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		ft_error("Error: allocation failed\n", cubed);
	
}

int	file_checker(int fd_file, t_cubed *cubed)
{
	char	*line;
	int		i;
	
	line = get_next_line(fd_file);
	if (!line)
		ft_error("Error: reading of file failed\n", cubed);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i, "WE", 2))
			textures_check(line + i, cubed);
		else if (line[i] == 'F' || line[i] == 'C')
			surfaces_check(line, cubed);
		else if (line[i] != '\n')
			check_map(line, cubed);
		free(line);
		line = get_next_line(fd_file);
	}
	free(line);
	return (1);
}

int	check_file(char *map, t_cubed *cubed)
{
	int		fd_file;

	fd_file = open(map, __O_DIRECTORY | 0677);
	if (fd_file)
		ft_error("Error: Cub3d does not accept directories\n", cubed);
	fd_file = open(map, O_RDONLY | 0677);
	if (!fd_file)
		ft_error("Error: opening file failed\n", cubed);
	file_checker(fd_file, cubed);
	return (0);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_putendl_fd(USAGE, 2), 0);
	check_file(argv[1], cubed);
	
	return (1);
}

