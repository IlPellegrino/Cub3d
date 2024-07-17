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
	black = 0x00000000
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