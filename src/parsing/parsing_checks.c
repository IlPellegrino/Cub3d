/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:36:40 by nromito           #+#    #+#             */
/*   Updated: 2024/07/19 17:22:39 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_double_player(t_cubed *cubed, int *flag, int col, int l)
{
	if ((cubed->map[col][l] == 'N' || cubed->map[col][l] == 'S'
		|| cubed->map[col][l] == 'W' || cubed->map[col][l] == 'E') && (*flag))
		return (1);
	return (0);
}

int	is_a_player(t_cubed *cubed, int *flag, int col, int l)
{
	if ((cubed->map[col][l] == 'N' || cubed->map[col][l] == 'S'
		|| cubed->map[col][l] == 'W' || cubed->map[col][l] == 'E') && !(*flag))
	{
		(*flag)++;
		if (cubed->map[col - 1][l] != '0' && cubed->map[col - 1][l] != '1'
			&& (cubed->map[col - 1][l] != 'N' && cubed->map[col - 1][l] != 'S'
			&& cubed->map[col - 1][l] != 'W' && cubed->map[col - 1][l] != 'E'
			&& (*flag)))
			return (0);
		if (cubed->map[col + 1][l] != '0' && cubed->map[col + 1][l] != '1'
			&& (cubed->map[col + 1][l] != 'N' && cubed->map[col + 1][l] != 'S'
			&& cubed->map[col + 1][l] != 'W' && cubed->map[col + 1][l] != 'E'
			&& (*flag)))
			return (0);
	}
	else if (is_double_player(cubed, flag, col, l))
		return (0);
	return (1);
}

int	is_a_zero(t_cubed *cubed, int *flag, int col, int l)
{
	if (cubed->map[col][l] == '0')
	{
		if (cubed->map[col - 1][l] != '0' && cubed->map[col - 1][l] != '1'
			&& (cubed->map[col - 1][l] != 'N' && cubed->map[col - 1][l] != 'S'
			&& cubed->map[col - 1][l] != 'W' && cubed->map[col - 1][l] != 'E'
			&& (*flag)))
			return (0);
		if (cubed->map[col + 1][l] != '0' && cubed->map[col + 1][l] != '1'
			&& (cubed->map[col + 1][l] != 'N' && cubed->map[col + 1][l] != 'S'
			&& cubed->map[col + 1][l] != 'W' && cubed->map[col + 1][l] != 'E'
			&& (*flag)))
			return (0);
	}
	return (1);
}

static int	check_pos(t_cubed *cubed, int col, int l)
{
	int			len;
	static int	flag;

	len = ft_strlen(cubed->map[col]);
	printf("map = %c", cubed->map[col][l]);
	if (cubed->map[col][0] != '1' && cubed->map[col][len - 1] != '1')
		ft_error("Error: DIOPORCO map\n", cubed);
	if (!is_a_player(cubed, &flag, col, l))
		ft_error("Error: invalid map\n", cubed);
	if (!is_a_zero(cubed, &flag, col, l))
		ft_error("Error: invalid map\n", cubed);
	return (flag);
}

void	check_map(t_cubed *cubed)
{
	int	i;
	int	j;
	int flag;

	i = -1;
	while (cubed->map[++i])
	{
		j = -1;
		while (cubed->map[i][++j])
		{
			if (j == 0)
				while (ft_isspace(cubed->map[i][j]))
					j++;
			if (i == 0 || i == cubed->game->ht - 1)
			{
				if (cubed->map[i][j] != '1')
					ft_error("Error: invalid map\n", cubed);
			}
			else
				flag = check_pos(cubed, i, j);
		}
	}
	if (!flag)
		ft_error("Error: no player found\n", cubed);
	cubed->game->counter += 1;
}
