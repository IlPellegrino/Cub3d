/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:43 by nromito           #+#    #+#             */
/*   Updated: 2024/07/11 11:47:40 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

#define HEIGHT 480
#define WIDTH 640
#define MAPW 24
#define MAPH 24

typedef struct s_game
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	
}			t_game;



#endif