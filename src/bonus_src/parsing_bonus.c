/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/08/06 17:05:58 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	copy_file(int fd, t_cubed *cubed)
{
	int		i;
	char	*line;

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

int	check_type(char *map, int fd, t_cubed *cubed)
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
			{
				close(fd);
				ft_error("Error: Cub3D accepts only `.cub' files\n", cubed);
			}
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
	check_type(map, fd, cubed);
	fd = open(map, O_RDONLY, 0677);
	if (fd < 0)
		ft_error("Error: File does not exist\n", cubed);
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
	int	i;

	i = -1;
	cubed->player = malloc(sizeof(t_player));
	while (++i < FRAME_NUMBER)
		cubed->door_anim[i].img = 0;
	cubed->weapon[0].img = 0;
	cubed->game = ft_calloc(sizeof (t_game), 1);
	cubed->game->anim_state = -1;
	cubed->map = 0;
	cubed->game->counter = 0;
	cubed->img = 0;
	cubed->win = 0;
	cubed->raycast = 0;
	cubed->keys = 0;
	cubed->mlx = 0;
	cubed->settings = 0;
	cubed->game->ceiling_cl = 0;
	cubed->game->floor_cl = 0;
	cubed->gui = 0;
	i = -1;
	while (++i < 5)
		cubed->texture[i].img = 0;
	return (1);
}

int	parsing(char **argv, int argc, t_cubed *cubed)
{
	if (argc != 2)
		return (ft_putendl_fd(USAGE, 0), 0);
	partial_init(cubed);
	check_file(argv[1], cubed);
	cubed->map = ft_calloc(sizeof (char **), cubed->game->ht + 2);
	syntax_checker(cubed);
	if (!cubed->game->no || !cubed->game->so
		|| !cubed->game->ea || !cubed->game->we)
		ft_error("Error: invalid texture direction\n", cubed);
	check_map(cubed);
	count_width(cubed);
	return (1);
}
