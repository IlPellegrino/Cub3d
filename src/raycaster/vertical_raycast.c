/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:26:38 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 18:58:35 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	door_ver_ray(t_cubed *cubed, t_raycast *ray, int map_x, int map_y)
{
	if (map_x >= 0 && map_x < cubed->map_w && map_y >= 0 && map_y < cubed->map_h
		&& (is_door(cubed, map_x, map_y) || cubed->map[map_y][map_x] == '1'))
	{
		ray->vx = ray->ver_x;
		ray->vy = ray->ver_y;
		ray->dof = cubed->map_w;
	}
	else
	{
		ray->ver_x += ray->ver_stepx;
		ray->ver_y += ray->ver_stepy;
		ray->dof += 1;
	}
}

void	wall_ver_ray(t_cubed *cubed, t_raycast *ray, int map_x, int map_y)
{
	if (map_x >= 0 && map_x < cubed->map_w && map_y >= 0 && map_y < cubed->map_h
		&& cubed->map[map_y][map_x] == '1')
	{
		ray->vx = ray->ver_x;
		ray->vy = ray->ver_y;
		ray->dof = cubed->map_w;
	}
	else
	{
		ray->ver_x += ray->ver_stepx;
		ray->ver_y += ray->ver_stepy;
		ray->dof += 1;
	}
}

void	ver_loop(t_cubed *cubed, t_raycast *ray, int flag)
{
	int map_x;
	int map_y;
	
	while (ray->dof < cubed->map_w)
	{
		map_x = (int)(ray->ver_x) / TILE_SIZE;
		map_y = (int)(ray->ver_y) / TILE_SIZE;
		if (map_y < 0)
			map_y = 0;
		if (map_y >= cubed->map_h)
			map_y = cubed->map_h - 1;
		cubed->map_w = ft_strlen(cubed->map[map_y]);
		printf("flag = %d\n", flag);
		if (flag)
			door_ver_ray(cubed, ray, map_x, map_y);
		else
			wall_ver_ray(cubed, ray, map_x, map_y);
	}
}

void	calculate_ver(t_raycast *ray, t_player *p)
{
	ray->ra_tan = -tan(ray->ra);
	if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
	{
		ray->ver_x = (((int)p->x / TILE_SIZE) * TILE_SIZE) - 0.0001;
		ray->ver_y = (p->x - ray->ver_x) * ray->ra_tan + p->y;
		ray->ver_stepx = -TILE_SIZE;
		ray->ver_stepy = -ray->ver_stepx * ray->ra_tan;
	}
	else
	{
		ray->ver_x = (((int)p->x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		ray->ver_y = (p->x - ray->ver_x) * ray->ra_tan + p->y;
		ray->ver_stepx = TILE_SIZE;
		ray->ver_stepy = -ray->ver_stepx * ray->ra_tan;
	}
}
