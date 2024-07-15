/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/12 15:38:07 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int ft_error(char *error)
{
	ft_putendl_fd(error, 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	(void)game;
	
	//parsing(game, argc, argv);
	/*if (argv[1] && argc == 2)
	{
		if (check_map(argv[1]))
			return (ft_error("Invalid map\n", 2));
		init_vars(&game);
		screen_setting(&game, argv[1]);
	}
	else
		ft_error("Wrong number of arguments\n", 2);*/
	printf("This is Cub3D!\n");
	return (0);
}
