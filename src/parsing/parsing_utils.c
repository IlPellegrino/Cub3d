/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:33:33 by nromito           #+#    #+#             */
/*   Updated: 2024/08/05 19:50:25 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_double_player(t_cubed *cubed, int *flag, int rows, int col)
{
	if ((cubed->map[rows][col] == 'N' || cubed->map[rows][col] == 'S'
		|| cubed->map[rows][col] == 'W' || cubed->map[rows][col] == 'E')
			&& (*flag))
		return (1);
	return (0);
}

void	set_player(t_cubed *cubed, char c)
{
	if (c == 'N')
		cubed->player->angle = PI / 2;
	else if (c == 'S')
		cubed->player->angle = 3 * PI / 2;
	else if (c == 'W')
		cubed->player->angle = WEST;
	else if (c == 'E')
		cubed->player->angle = EAST;
}

int	copy_map(t_cubed *cubed, int *k, int *i, int *flag)
{
	(*flag) = 1;
	while (cubed->game->cub[(*i)][(*k)])
	{
		if (!is_legal(cubed->game->cub[(*i)][(*k)])
			&& !ft_isspace(cubed->game->cub[(*i)][(*k)]))
			ft_error("Error: invalid character in map\n", cubed);
		(*k)++;
	}
	if (cubed->game->cub[(*i)][(*k) - 1] == '\n')
		cubed->game->cub[(*i)][(*k) - 1] = '\0';
	cubed->map[cubed->game->counter++] = ft_strdup(cubed->game->cub[(*i)]);
	return (1);
}

int	syntax_checker(t_cubed *cubed)
{
	int	i;
	int	k;
	int	flag;

	i = -1;
	flag = 0;
	while (cubed->game->cub[++i])
	{
		k = 0;
		while (ft_isspace(cubed->game->cub[i][k]))
			k++;
		if ((!ft_strncmp(cubed->game->cub[i] + k, "NO", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "SO", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "EA", 2)
			|| !ft_strncmp(cubed->game->cub[i] + k, "WE", 2)) && !flag)
			textures_check(cubed->game->cub[i], cubed);
		else if ((cubed->game->cub[i][k] == 'F' || cubed->game->cub[i][k] == 'C')
			&& !flag)
			surfaces_check(cubed->game->cub[i], cubed);
		else if (is_legal(cubed->game->cub[i][k]) || cubed->game->cub[i][k] == 'F'
			|| cubed->game->cub[i][k] == 'C')
			copy_map(cubed, &k, &i, &flag);
	}
	return (1);
}
