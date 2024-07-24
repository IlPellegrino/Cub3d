/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:36:40 by nromito           #+#    #+#             */
/*   Updated: 2024/07/24 20:27:46 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	is_double_player(t_cubed *cubed, int *flag, int l, int col)
{
	if ((cubed->map[l][col] == 'N' || cubed->map[l][col] == 'S'
		|| cubed->map[l][col] == 'W' || cubed->map[l][col] == 'E') && (*flag))
		return (1);
	return (0);
}

int is_acceptable(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'D')
		return (1);
	return (0);
}

int	is_a_player(t_cubed *cubed, int *flag, int l, int col)
{
	if ((cubed->map[l][col] == 'N' || cubed->map[l][col] == 'S'
		|| cubed->map[l][col] == 'W' || cubed->map[l][col] == 'E') && !(*flag))
	{
		(*flag)++;
		if (!is_acceptable(cubed->map[l - 1][col]))
			return (0);
		if (!is_acceptable(cubed->map[l + 1][col]))
			return (0);
	}
	else if (is_double_player(cubed, flag, l, col))
		return (0);
	return (1);
}

int	is_a_zero(t_cubed *cubed, int l, int col)
{
	if (cubed->map[l][col] == '0')
	{
		if (!is_acceptable(cubed->map[l - 1][col]))
			return (0);
		if (!is_acceptable(cubed->map[l + 1][col]))
			return (0);
	}
	return (1);
}

static int	check_pos(t_cubed *cubed, int l, int col)
{
	int			len;
	static int	flag;
	char		*tr_tmp;

	tr_tmp = ft_rev_trim(cubed->map[l], " ");
	free(cubed->map[l]);
	cubed->map[l] = ft_strdup(tr_tmp);
	len = ft_strlen(cubed->map[l]);
	if (cubed->map[l][col] != '1' || cubed->map[l][len - 1] != '1')
		ft_error("Error: invalid map\n", cubed);
	while (cubed->map[l][col])
	{
		if (!check_chars(cubed->map, l, col))
			ft_error("Error: IN map\n", cubed);
		if (!is_a_player(cubed, &flag, l, col))
			ft_error("Error: invalid map\n", cubed);
		if (!is_a_zero(cubed, l, col))
			ft_error("Error: invalid map\n", cubed);
		col++;
	}
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
		j = 0;
		while (ft_isspace(cubed->map[i][j]))
			j++;
		if (i == 0 || i == cubed->game->ht - 1)
		{
			while ((cubed->map[i][j] == '1'  || cubed->map[i][j] == ' ')
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
	// cubed->game->counter += 1;
}
