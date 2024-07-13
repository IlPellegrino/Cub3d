/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/12 16:29:30 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	main(int argc, char **argv)
{
	t_cubed		cubed;
	
	//parsing(game, argc, argv);
	if (argv[1] && argc == 2)
	{
		if (check_map(argv[1]))
			return (ft_error("Invalid map\n", &cubed));
		screen_setting(&cubed);
	}
	else
		ft_error("Wrong number of arguments\n", &cubed);
	printf("This is Cub3D!\n");
	return (0);
}
