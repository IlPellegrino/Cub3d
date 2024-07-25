/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/25 19:22:33 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	syntax_checker(t_cubed *cubed)
{
	int	i;
	int	k;

	i = -1;
	while (cubed->game->cub[++i])
	{
		k = 0;
		while (ft_isspace(cubed->game->cub[i][k]))
			k++;
		if (!ft_strncmp(cubed->game->cub[i] + k, "NO", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "SO", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "EA", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "WE", 2))
			textures_check(cubed->game->cub[i], cubed);
		else if (cubed->game->cub[i][k] == 'F' || cubed->game->cub[i][k] == 'C')
			surfaces_check(cubed->game->cub[i], cubed);
		else if (is_legal(cubed->game->cub[i][k]))
		{
			while (cubed->game->cub[i][k])
			{
				if (!is_legal(cubed->game->cub[i][k]) && !ft_isspace(cubed->game->cub[i][k]))
					ft_error("Error: invalid character in map\n", cubed);
				k++;
			}
			if (cubed->game->cub[i][k - 1] == '\n')
				cubed->game->cub[i][k - 1] = '\0';
			cubed->map[cubed->game->counter++] = ft_strdup(cubed->game->cub[i]);
		}
	}
	return (1);
}

int	copy_file(int fd, t_cubed *cubed)
{
	char	*line;
	int		i;
	
	i = -1;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_error("Error: reading of file failed\n", cubed);
	}
	while (line)
	{
		cubed->game->cub[++i] = ft_strdup(line);
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
	int	fd;
	int	h;

	fd = open(map, __O_DIRECTORY, 0677);
	if (fd > 0)
	{
		close(fd);
		ft_error("Error: Cub3D does not accept directories\n", cubed);
	}
	check_type(map);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
		ft_error("Error: Cub3D accepts only '.cub' files\n", cubed);
	h = count_map_columns(fd, cubed);
	if (fd)
		close (fd);
	cubed->game->cub = ft_calloc(sizeof (char **), h + 1);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
		ft_error("Error: Cub3D accepts only '.cub' files\n", cubed);
	copy_file(fd, cubed);
	if (fd)
		close(fd);
	return (0);
}

int	partial_init(t_cubed *cubed)
{
	cubed->player = malloc(sizeof(t_player));
	if (!cubed->player)
		ft_error("Error: malloc failed\n", cubed);
	cubed->game = ft_calloc(sizeof (t_game), 1);
	cubed->map = 0;
	cubed->game->counter = 0;
	cubed->img = 0;
	cubed->win = 0;
	cubed->raycast = 0;
	cubed->keys = 0;
	cubed->mlx = 0;
	return (1);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_putendl_fd(USAGE, 0), 0);
	partial_init(cubed);
	check_file(argv[1], cubed);
	cubed->map = ft_calloc(sizeof (char **), cubed->game->ht + 1);
	syntax_checker(cubed);
	if (!cubed->game->no || !cubed->game->so
		|| !cubed->game->ea || !cubed->game->we)
		ft_error("Error: invalid texture direction\n", cubed);
	check_map(cubed);
	print_matrix(cubed->map);
	count_width(cubed);
	return (1);
}
