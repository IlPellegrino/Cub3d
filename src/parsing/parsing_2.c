/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:39:31 by nromito           #+#    #+#             */
/*   Updated: 2024/07/20 18:17:44 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	count_map_columns(int fd, t_cubed *cubed)
{
	int		h;
	int		i;
	char	*line;

	h = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		ft_error("Error: Read of file failed\n", cubed);
	}
	while (line)
	{
		h++;
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1' || line[i] == '0')
			cubed->game->ht++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (h);
}

int	count_width(t_cubed *cubed)
{
	int	h;

	h = -1;
	while (cubed->map[++h])
	{
		if ((int)ft_strlen(cubed->map[h]) > cubed->game->wd)
			cubed->game->wd = ft_strlen(cubed->map[h]);
	}
	return (1);
}

int	check_chars(char **map, int l, int col)
{
	if (map[l][col] == '1')
		return (1);
	if (map[l][col] == '0')
		return (1);
	if (map[l][col] == 'N')
		return (1);
	if (map[l][col] == 'E')
		return (1);
	if (map[l][col] == 'W')
		return (1);
	if (map[l][col] == 'S')
		return (1);
	if (map[l][col] == ' ')
		return (1);
	return (0);
}
