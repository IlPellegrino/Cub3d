/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:27:43 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 19:55:50 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	door_ray(t_cubed *cubed, t_raycast *ray, int map_x, int map_y)
{
	if (map_x >= 0 && map_x < cubed->map_w && map_y >= 0 && map_y < cubed->map_h
		&& (is_door(cubed, map_x, map_y) || cubed->map[map_y][map_x] == '1'))
	{
		ray->hx = ray->hor_x;
		ray->hy = ray->hor_y;
		ray->dof = cubed->map_h;
	}
	else
	{
		ray->hor_x += ray->hor_stepx;
		ray->hor_y += ray->hor_stepy;
		ray->dof += 1;
	}
}

void	wall_ray(t_cubed *cubed, t_raycast *ray, int map_x, int map_y)
{
	if (map_x >= 0 && map_x < cubed->map_w && map_y >= 0 && map_y < cubed->map_h
		&& cubed->map[map_y][map_x] == '1')
	{
		ray->hx = ray->hor_x;
		ray->hy = ray->hor_y;
		ray->dof = cubed->map_h;
	}
	else
	{
		ray->hor_x += ray->hor_stepx;
		ray->hor_y += ray->hor_stepy;
		ray->dof += 1;
	}
}

void	hor_loop(t_cubed *cubed, t_raycast *ray, int flag)
{
	int	map_x;
	int	map_y;

	while (ray->dof < cubed->map_h)
	{
		map_x = (int)(ray->hor_x) / TILE_SIZE;
		map_y = (int)(ray->hor_y) / TILE_SIZE;
		if (map_y < 0)
			map_y = 0;
		if (map_y >= cubed->map_h)
			map_y = cubed->map_h - 1;
		cubed->map_w = ft_strlen(cubed->map[map_y]);
		if (flag)
			door_ray(cubed, ray, map_x, map_y);
		else
			wall_ray(cubed, ray, map_x, map_y);
	}
}

void	calculate_hor(t_cubed *cubed, t_raycast *ray)
{
	t_player	*p;

	p = cubed->player;
	if (ray->ra > PI)
	{
		ray->hor_y = (((int)p->y / TILE_SIZE) * TILE_SIZE) - 0.0001;
		ray->hor_x = (p->y - ray->hor_y) * ray->a_tan + p->x;
		ray->hor_stepy = -TILE_SIZE;
		ray->hor_stepx = -ray->hor_stepy * ray->a_tan;
	}
	else if (ray->ra < PI)
	{
		ray->hor_y = (((int)p->y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		ray->hor_x = (p->y - ray->hor_y) * ray->a_tan + p->x;
		ray->hor_stepy = TILE_SIZE;
		ray->hor_stepx = -ray->hor_stepy * ray->a_tan;
	}
	else
	{
		ray->hor_x = p->x;
		ray->hor_y = p->y;
		ray->dof = cubed->game->ht;
	}
}
