/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:00:14 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/05 19:48:38 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/**======================
 *?    	 MATH
 *========================**/
# define PI 3.14159265359
# define DR 0.0174533
# define WEST PI
# define EAST 0
/**======================
 *?    	 SCREEN
 *========================**/
# define WIDTH 1080
# define HEIGHT 540
# define MINIMAP_SIZE 200
/**======================
 *?    	 TILES
 *========================**/
# define TILE_SIZE 64
# define MINI_SIZE 12
# define FRAME_NUMBER 21
/**======================
 *?   PLAYER SETTINGS
 *========================**/
# define ROTATION_SPEED 5
# define SENSITIVITY 2
# define PLAYER_SIZE 7
# define PLAYER_SPEED 30
# define FOV 80
# define CROSS_SIZE 14
/* ------------------------*/
# define F 1
# define C 2
/*-------------------------*/
# define DOOR_PATH "src/textures/door animation/frame_"

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
	down = 65364,
	space = 32,
	plus = 65451,
	minus = 65453,
	page_up = 65365,
	page_down = 65366,
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
	periwinkle = 0x00ccccff,
	tea_green = 0x00d0f0c0,
	jet = 0x00000099,
	eggplant = 0x006D435A,
	lion = 0x00C19A6B,
	snow = 0x00FFFAFA,
	claret = 0x00DC143C,
	rich_black = 0x00004040,
	black_coral = 0x0054626F,
};

#endif