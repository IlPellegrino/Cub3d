/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:36:40 by nromito           #+#    #+#             */
/*   Updated: 2024/08/05 15:48:34 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_a_player(t_cubed *cubed, int *flag, int rows, int col)
{
	if ((cubed->map[rows][col] == 'N' || cubed->map[rows][col] == 'S'
		|| cubed->map[rows][col] == 'W' || cubed->map[rows][col] == 'E')
			&& !(*flag))
	{
		(*flag)++;
		set_player(cubed, cubed->map[rows][col]);
		cubed->player->map_x = col;
		cubed->player->map_y = rows;
		if (!is_acceptable(cubed->map[rows - 1][col]))
			return (0);
		if (!is_acceptable(cubed->map[rows + 1][col]))
			return (0);
	}
	else if (is_double_player(cubed, flag, rows, col))
		return (0);
	return (1);
}

int	is_a_zero(t_cubed *cubed, int rows, int col)
{
	if (cubed->map[rows][col] == '0')
	{
		if (!is_acceptable(cubed->map[rows - 1][col]))
			return (0);
		if (!is_acceptable(cubed->map[rows + 1][col]))
			return (0);
		if (!is_acceptable(cubed->map[rows - 1][col + 1]))
			return (0);
		if (!is_acceptable(cubed->map[rows + 1][col + 1]))
			return (0);
		if (!is_acceptable(cubed->map[rows - 1][col - 1]))
			return (0);
		if (!is_acceptable(cubed->map[rows + 1][col - 1]))
			return (0);
	}
	return (1);
}

int	is_a_door(t_cubed *cubed, int rows, int col)
{
	if (cubed->map[rows][col] == 'D')
	{
		if (cubed->map[rows - 1][col] == '1'
			&& cubed->map[rows + 1][col] == '1'
			&& cubed->map[rows][col + 1] == '1'
			&& cubed->map[rows][col - 1] == '1')
			return (0);
		if (cubed->map[rows - 1][col] != '1'
			&& cubed->map[rows + 1][col] != '1'
			&& cubed->map[rows][col + 1] != '1'
			&& cubed->map[rows][col - 1] != '1')
			return (0);
		if ((cubed->map[rows - 1][col] == '1'
			&& cubed->map[rows + 1][col] == '1')
			|| (cubed->map[rows][col + 1] == '1'
			&& cubed->map[rows][col - 1] == '1'))
			return (1);
		else
			return (0);
	}
	return (1);
}

static int	check_pos(t_cubed *cubed, int rows, int col)
{
	int			len;
	static int	flag;
	char		*tr_tmp;

	tr_tmp = ft_rev_trim(cubed->map[rows], " ");
	free(cubed->map[rows]);
	cubed->map[rows] = ft_strdup(tr_tmp);
	free(tr_tmp);
	len = ft_strlen(cubed->map[rows]);
	if (cubed->map[rows][col] != '1' || cubed->map[rows][len - 1] != '1')
		ft_error("Error: invalid map\n", cubed);
	while (cubed->map[rows][col])
	{
		if (!check_chars(cubed->map, rows, col))
			ft_error("Error: invalid map\n", cubed);
		if (!is_a_player(cubed, &flag, rows, col))
			ft_error("Error: invalid map\n", cubed);
		if (!is_a_zero(cubed, rows, col))
			ft_error("Error: invalid map\n", cubed);
		if (!is_a_door(cubed, rows, col))
			ft_error("Error: invalid map\n", cubed);
		col++;
	}
	return (flag);
}

void	check_map(t_cubed *cubed)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (cubed->map[++i])
	{
		j = 0;
		while (ft_isspace(cubed->map[i][j]))
			j++;
		if (i == 0 || i == cubed->game->ht - 1)
		{
			while ((cubed->map[i][j] == '1' || cubed->map[i][j] == ' ')
				&& cubed->map[i][j])
				j++;
			if (cubed->map[i][j])
				ft_error("Error: invalid map\n", cubed);
		}
		else
			flag = check_pos(cubed, i, j);
	}
	if (!flag)
		ft_error("Error: no player found\n", cubed);
}
