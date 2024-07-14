/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:49:02 by nromito           #+#    #+#             */
/*   Updated: 2024/07/14 15:59:44 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_map(char *map)
{
	int	fd_map;

	fd_map = open(map, O_RDONLY | 0677);
	(void)fd_map;
	return (0);
}

int	parsing(char **argv, int argc)
{
	(void)argc;
	(void)argv;
	return (1);	
}

