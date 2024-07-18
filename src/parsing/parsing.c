/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/18 19:38:07 by nromito          ###   ########.fr       */
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
		if (ft_strchr(line, '1'))
			cubed->game->ht += 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (1);
}

void	check_pos(char **pos, t_cubed *cubed, int col, int l)
{
	static int	flag;

	if (pos[col][0] != '1' && pos[col][ft_strlen(pos[col]) - 1] != '1') // check walls
		ft_error("Error: invalid map\n", cubed);
	if ((pos[col][l] == 'N' || pos[col][l] == 'S'
		|| pos[col][l] == 'W' || pos[col][l] == 'E') && !flag) // player
	{
		flag++;
		if (pos[col - 1][l] != '0' && pos[col - 1][l] != '1' // check line up
				&& (pos[col - 1][l] != 'N' && pos[col - 1][l] != 'S'
				&& pos[col - 1][l] != 'W' && pos[col - 1][l] != 'E'
				&& cubed->game->p_flag == 1))
			ft_error("Error: zio map\n", cubed);
		if (pos[col + 1][l] != '0' && pos[col + 1][l] != '1'
			&& (pos[col + 1][l] != 'N' && pos[col + 1][l] != 'S'
			&& pos[col + 1][l] != 'W' && pos[col + 1][l] != 'E'
			&& cubed->game->p_flag == 1)) // check line down
			ft_error("Error: DIO map\n", cubed);
	}
	else if ((pos[col][l] == 'N' || pos[col][l] == 'S'
		|| pos[col][l] == 'W' || pos[col][l] == 'E') && flag) //2 players
		ft_error("Error: cacca map\n", cubed);
	if (pos[col][l] == '0')     // zero
	{
		if (pos[col - 1][l] != '0' && pos[col - 1][l] != '1' // check line up
				&& (pos[col - 1][l] != 'N' && pos[col - 1][l] != 'S'
				&& pos[col - 1][l] != 'W' && pos[col - 1][l] != 'E'
				&& cubed->game->p_flag == 1))
			ft_error("Error: bella map\n", cubed);
		if (pos[col + 1][l] != '0' && pos[col + 1][l] != '1'
			&& (pos[col + 1][l] != 'N' && pos[col + 1][l] != 'S'
			&& pos[col + 1][l] != 'W' && pos[col + 1][l] != 'E'
			&& cubed->game->p_flag == 1)) // check line down
			ft_error("Error: DIO map\n", cubed);
	}
}

void	check_map(t_cubed *cubed)
{
	int	i;
	int	j;

	i = -1;
	while (cubed->map[++i])
	{
		j = -1;
		while (cubed->map[i][++j])
		{
			if (j == 0)
				while (ft_isspace(cubed->map[i][j]))
					j++;
			if (i == 0 || i == cubed->game->ht) // prima e ultima riga della mappa
			{
				if (cubed->map[i][j] != '1')
					ft_error("Error: zio map\n", cubed);
			}
			else // resto della mappa
				check_pos(cubed->map, cubed, i, j);
		}
	}
	cubed->game->counter += 1;
}

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
			textures_check(line + i, cubed, fd);
		else if (line[i] == 'F' || line[i] == 'C')
			surfaces_check(line + i, cubed, fd);
		else if (line[i] == '1')
		{
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

int	check_void_path(t_cubed *cubed)
{
	if (!cubed->game->no || !cubed->game->so || !cubed->game->ea
		|| !cubed->game->we)
		ft_error("Error: invalid texture direction\n", cubed);
	return (1);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_error(USAGE, cubed), 0);
	check_file(argv[1], cubed);
	check_void_path(cubed);
	// print_matrix(cubed->map);
	check_map(cubed);
	// count_width_height();
	return (1);
}
