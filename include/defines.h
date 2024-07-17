#ifndef DEFINES_H
# define DEFINES_H

# define USAGE "\nInvalid argument\nUsage: ./cub3d path/to/map\n"

#define PI 3.14159265359

# define WIDTH 1900 // screen width
# define HEIGHT 1000 // screen height

# define TILE_SIZE 32 // tile size

# define FOV 60 // field of view

# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SIZE 8 // player size
# define PLAYER_SPEED 4 // player speed

# define F 1
# define C 2

enum colors{
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
	cyan = 0x00ffff00,
	olive = 0x00808000,
	maroon = 0x00800000,
	navy = 0x00000080,
};

enum keys{
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
	f = 102
};

#endif