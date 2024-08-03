/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 19:08:34 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

double	init_vars(t_cubed *cubed, t_raycast *ray)
{
	double angle_step;

	cubed->map_h = cubed->game->ht;
	angle_step = RADIANS_FOV / WIDTH;
	ray->half_fov = RADIANS_FOV / 2;
	ray->half_screen = WIDTH / 2;
	ray->r = -1;
	return (angle_step);
}

void render_doors(t_cubed *cubed, t_wall *wall)
{
	t_player	*p;
	t_raycast	*ray;
	int			flag;
	double		angle_step;
	double		correctedDist;

	ray = cubed->raycast;
	p = cubed->player;
	angle_step = init_vars(cubed, ray);
	while (++ray->r < WIDTH)
	{
		flag = 1;
		angle_ray(ray, p);
		calculate_hor(cubed, ray);
		hor_loop(cubed, ray, flag);
		ray->dof = 0;
		calculate_ver(ray, p);
		ver_loop(cubed, ray, flag);
		flag = calculate_dir(ray, p, &wall->final_dist);
		correctedDist = wall->final_dist * cos(ray->ray_angle - p->angle);
		wall->wall_height = (TILE_SIZE * HEIGHT) / correctedDist;
		call_door_wall(cubed, wall, ray, flag);
	}
}

void rendering(t_cubed *cubed)
{
	t_raycast *ray;
	t_player *p;
	t_wall wall;
	int map_w;
	int map_h;

	map_h = cubed->game->ht;
	p = cubed->player;
	ray = cubed->raycast;
	ray->half_fov = RADIANS_FOV / 2;
	ray->half_screen = WIDTH / 2;
	// double initial_angle = p->angle - (RADIANS_FOV / 2);
	for (ray->r = 0; ray->r < WIDTH; ray->r++)
	{
		angle_ray(ray, p);
		// Calculate horizontal intersection
		ray->dof = 0;
		calculate_hor(cubed, ray);
		while (ray->dof < map_h)
		{
			int mapX = (int)(ray->hor_x) / TILE_SIZE;
			int mapY = (int)(ray->hor_y) / TILE_SIZE;
			if (mapY < 0)
				mapY = 0;
			if (mapY >= map_h)
				mapY = map_h - 1;
			map_w = 40;
			if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && cubed->map[mapY][mapX] == '1')
			{
				ray->hx = ray->hor_x;
				ray->hy = ray->hor_y;
				ray->dof = map_h;
			}
			else
			{
				ray->hor_x += ray->hor_stepx;
				ray->hor_y += ray->hor_stepy;
				ray->dof += 1;
			}
		}
		// Calculate vertical intersection
		double verX, verY, verStepX, verStepY;
		ray->dof = 0;
		double nTan = -tan(ray->ra);
		if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
		{
			verX = (((int)p->x / TILE_SIZE) * TILE_SIZE) - 0.0001;
			verY = (p->x - verX) * nTan + p->y;
			verStepX = -TILE_SIZE;
			verStepY = -verStepX * nTan;
		}
		else
		{
			verX = (((int)p->x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			verY = (p->x - verX) * nTan + p->y;
			verStepX = TILE_SIZE;
			verStepY = -verStepX * nTan;
		}
		while (ray->dof < map_w)
		{
			int mapX = (int)(verX) / TILE_SIZE;
			int mapY = (int)(verY) / TILE_SIZE;
			if (mapY < 0)
				mapY = 0;
			if (mapY >= map_h)
				mapY = map_h - 1;
			map_w = 40;
			if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && cubed->map[mapY][mapX] == '1')
			{
				ray->vx = verX;
				ray->vy = verY;
				ray->dof = map_w;
			}
			else
			{
				verX += verStepX;
				verY += verStepY;
				ray->dof += 1;
			}
		}
		int flag;
		// Select the closest hit
		double distH = sqrt((p->x - ray->hor_x) * (p->x - ray->hor_x) + (p->y - ray->hor_y) * (p->y - ray->hor_y));
		double distV = sqrt((p->x - verX) * (p->x - verX) + (p->y - verY) * (p->y - verY));
		double finalDist;
		if (distH < distV)
		{
			if (ray->ra > 0 && ray->ra < PI)
				flag = 0; // north
			else
				flag = 1; // south
			ray->rx = ray->hor_x;
			ray->ry = ray->hor_y;
			finalDist = distH;
		}
		else
		{
			if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
				flag = 2; // east
			else
				flag = 3; // west
			ray->rx = verX;
			ray->ry = verY;
			finalDist = distV;
		}
		// Correct the distance for the fish-eye effect
		double correctedDist = finalDist * cos(ray->ray_angle - p->angle);
		// Calculate wall height
		wall.wall_height = (TILE_SIZE * HEIGHT) / correctedDist;
		// Ensure wall height does not exceed the screen height
		// Calculate start and end positions for the wall slice
		wall.wall_top = (HEIGHT / 2) - (wall.wall_height / 2);
		if (wall.wall_top < 0)
			wall.wall_top = 0;
		wall.wall_bottom = wall.wall_top + wall.wall_height;
		if (wall.wall_bottom > HEIGHT)
			wall.wall_bottom = HEIGHT;
		// Draw the wall slice (a vertical line) on the screen
		// draw top half of the screen as the ceiling
		draw_vertical_line(cubed, 0, wall.wall_top, cyan);
		// draw bottom half of the screen as floor
		draw_vertical_line(cubed, wall.wall_bottom, HEIGHT, brown);
		draw_walls(cubed, &wall, flag);
	}
	render_doors(cubed, &wall);
}
