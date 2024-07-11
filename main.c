/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/11 15:40:27 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/cubed.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argv[1] && argc == 2)
	{
		if (check_map(argv[1]))
			return (ft_error("Invalid map\n", 2), 0);
		init_vars(&game);
		screen_setting(&game, argv[1]);
	}
	else
		ft_error("Wrong number of arguments\n", 2);
	return (0);
}
