/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:00:14 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/21 23:40:48 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/**======================
 *?    	 MATH
 *========================**/
# define PI 3.14159265359
# define DR 0.0174533
# define RADIANS_FOV (FOV * (PI / 180))
/**======================
 *?    	 SCREEN
 *========================**/
# define WIDTH 1080
# define HEIGHT 720
/**======================
 *?    	 TILES
 *========================**/
# define TILE_SIZE 32
# define MINI_SIZE 12
/**======================
 *?   PLAYER SETTINGS
 *========================**/
# define ROTATION_SPEED 2
# define PLAYER_SIZE 7
# define PLAYER_SPEED 10
# define FOV 60
/* ------------------------*/
# define F 1
# define C 2
/*-------------------------*/

enum e_keys
{
	esc = 65307,
	w = 119,
	a = 97,
	s = 115,
	d = 100,
	shift = 65505,
	tab = 65289,
	e = 101,
	q = 113,
	m = 109,
	f = 102,
	p = 112,
	r = 114,
	left = 65361,
	up = 65362,
	right = 65363,
	down = 65364
};

enum e_colors
{
	red = 0x00ff0000,
	green = 0x0000ff00,
	blue = 0x000000ff,
	white = 0x00ffffff,
	black = 0x00000000,
	grey = 0x00a9a9a9,
	yellow = 0x00ffff00,
	purple = 0x00800080,
	orange = 0x00ffa500,
	brown = 0x00a52a2a,
	pink = 0x00ff69b4,
	teal = 0x0000ffff,
	magenta = 0x00ff00ff,
	cyan = 0x0000ffff,
	olive = 0x00808000,
	maroon = 0x00800000,
	navy = 0x00000080,
	pastel = 0x00d1a6ff,
};


#endif