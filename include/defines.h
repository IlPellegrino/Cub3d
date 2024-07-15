#ifndef DEFINES_H
# define DEFINES_H

# define USAGE "\nInvalid argument\nUsage: ./cub3d path/to/map\n"

# define WIDTH 1900 // screen width
# define HEIGHT 1000 // screen height

# define TILE_SIZE 30 // tile size

# define FOV 60 // field of view

# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed

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