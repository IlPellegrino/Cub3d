/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:39:31 by nromito           #+#    #+#             */
/*   Updated: 2024/07/19 15:43:30 by nromito          ###   ########.fr       */
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
