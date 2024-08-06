/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:33:33 by nromito           #+#    #+#             */
/*   Updated: 2024/08/06 16:56:01 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	count_commas(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	return (comma);
}

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
		cubed->player->angle = 3 * PI / 2;
	else if (c == 'S')
		cubed->player->angle = PI / 2;
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
		if (is_texture(cubed, i, k) && !flag)
			textures_check(cubed->game->cub[i], cubed);
		else if ((cubed->game->cub[i][k] == 'F'
			|| cubed->game->cub[i][k] == 'C') && !flag)
			surfaces_check(cubed->game->cub[i], cubed);
		else if (is_legal(cubed->game->cub[i][k])
			|| cubed->game->cub[i][k] == 'F'
			|| cubed->game->cub[i][k] == 'C')
			copy_map(cubed, &k, &i, &flag);
		else if (cubed->game->cub[i][k] != 0 && cubed->game->cub[i][k] != '\n')
			ft_error("Error: invalid cub file\n", cubed);
	}
	return (1);
}
