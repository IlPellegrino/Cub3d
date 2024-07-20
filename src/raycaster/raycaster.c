/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/07/20 18:09:48 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	wall_hit(float x, float y, t_cubed *cubed)	// check the wall hit
{
	int		x_m;
	int		y_m;
    
	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= 10 || x_m >= 22))
		return (0);
	if (cubed->map[y_m] && x_m <= (int)strlen(cubed->map[y_m]))
		if (cubed->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int unit_circle(float angle, char c) // check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
		return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
		return (1);
	}
	return (0);
}

int inter_check(float angle, float *inter, float *step, int is_horizon)
{
    if (is_horizon)
    {
        if (angle > 0 && angle < PI)
        {
            *inter += TILE_SIZE;
            return (-1);
        }
        *step *= -1;
    }
    else
    {
        if (angle > PI / 2 && angle < 3 * PI / 2)
        {
            *inter += TILE_SIZE;
            return (-1);
        }
        *step *= -1;
    }
    return (1);
}

double ver_inters(t_cubed *cubed, double angle)
{
    float   xstep;
    float   ystep;
    float   v_x;
    float   v_y;
    int     pixel;

    xstep = TILE_SIZE;
    ystep = TILE_SIZE * tan(angle);
    v_x = floor(cubed->player->x / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angle, &v_x, &xstep, 0);
    v_y = cubed->player->y + (v_x - cubed->player->x) * tan(angle);
    if ((unit_circle(angle, 'x') && ystep < 0) || (!unit_circle(angle, 'x') && ystep > 0))
        ystep *= -1;
    while (wall_hit(v_x - pixel, v_y, cubed))
    {
        v_x += xstep;
        v_y += ystep;
    }
    return (sqrt(pow(v_x - cubed->player->x, 2) + pow(v_y - cubed->player->y, 2)));
}

double hor_inters(t_cubed *cubed, double angle)
{
    float   xstep;
    float   ystep;
    float   h_x;
    float   h_y;
    int     pixel;

    ystep = TILE_SIZE;
    xstep = TILE_SIZE / tan(angle);
    h_y = floor(cubed->player->y / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angle, &h_y, &ystep, 1);
    h_x = cubed->player->x + (h_y - cubed->player->y) / tan(angle);
    if ((unit_circle(angle, 'y') && xstep > 0) || (!unit_circle(angle, 'y') && xstep < 0))
        xstep *= -1;
    while (wall_hit(h_x, h_y - pixel, cubed))
    {
        h_x += xstep;
        h_y += ystep;
    }
    return (sqrt(pow(h_x - cubed->player->x, 2) + pow(h_y - cubed->player->y, 2)));
}

int check_angle(double angle)
{
    if (angle < PI)
        angle += 2 * PI;
    if (angle > 2 * PI)
        angle -= 2 * PI;
    return (angle);
}

void    draw_wall(t_cubed *cubed, int ray, int top_pix, int bot_pix)
{
    int     color;

    while (top_pix < bot_pix)
    {
        color = magenta;
        better_pixel_put(cubed->img, ray, top_pix++, color);
    }
}

void render_walls(t_cubed *cubed, int ray)
{
    double  wall_h;
    double  b_pix;
    double  t_pix;
    t_raycast *raycast = cubed->raycast;

    raycast->distance *= cos(check_angle(raycast->angle - cubed->player->angle));
    wall_h = (TILE_SIZE / raycast->distance) * ((WIDTH / 2) / tan(FOV / 2));
    b_pix = (HEIGHT / 2) + (wall_h / 2);
    t_pix = (HEIGHT / 2) - (wall_h / 2);
    if (b_pix > HEIGHT)
        b_pix = HEIGHT;
    if (t_pix < 0)
        t_pix = 0;
    draw_wall(cubed, ray, t_pix, b_pix);
}

void drawRays3D(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    //double fov_rd = (FOV * PI) / 180;
    double h_inter;
    double v_inter;
    ray->r = 0;
    ray->angle = p->angle - (FOV / 2);
    while (ray->r < WIDTH)
    {
        ray->hit = 0;
        h_inter = hor_inters(cubed, check_angle(ray->angle));
        v_inter = ver_inters(cubed, check_angle(ray->angle));
        if (v_inter <= h_inter)
            ray->distance = v_inter;
        else
        {
            ray->distance = h_inter;
            ray->hit = 1;
        }
        render_walls(cubed, ray->r);
        ray->r++;
        ray->angle += (FOV / WIDTH);
    }
}
