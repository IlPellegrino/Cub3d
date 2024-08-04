/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/08/04 16:26:49 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

double	init_vars(t_cubed *cubed, t_raycast *ray)
{
	double	angle_step;

	cubed->map_h = cubed->game->ht;
	angle_step = (FOV * PI / 180) / WIDTH;
	ray->half_fov = (FOV * PI / 180) / 2;
	ray->half_screen = WIDTH / 2;
	ray->r = -1;
	return (angle_step);
}

void	render_doors(t_cubed *cubed, t_wall *wall)
{
	t_player	*p;
	t_raycast	*ray;
	int			flag;
	double		corrected_dist;

	ray = cubed->raycast;
	p = cubed->player;
	ray->r = 0;
	while (++ray->r < WIDTH)
	{
		angle_ray(ray, p);
		calculate_hor(cubed, ray);
		hor_loop(cubed, ray, 1);
		ray->dof = 0;
		calculate_ver(ray, p);
		ver_loop(cubed, ray, 1);
		flag = calculate_dir(ray, p, &wall->final_dist, 1);
		corrected_dist = wall->final_dist * cos(ray->ray_angle - p->angle);
		wall->wall_height = (TILE_SIZE * HEIGHT) / corrected_dist;
		call_door_wall(cubed, wall, ray, flag);
	}
}

void	rendering(t_cubed *cubed)
{
	t_raycast	*ray;
	t_player	*p;
	t_wall		wall;
	int			flag;

	p = cubed->player;
	ray = cubed->raycast;
	cubed->map_h = cubed->game->ht;
	ray->half_fov = (FOV * PI / 180) / 2;
	ray->half_screen = WIDTH / 2;
	ray->r = -1;
	while (++ray->r < WIDTH)
	{
		angle_ray(ray, p);
		ray->dof = 0;
		calculate_hor(cubed, ray);
		hor_loop(cubed, ray, 0);
		ray->dof = 0;
		calculate_ver(ray, p);
		ver_loop(cubed, ray, 0);
		flag = calculate_dir(ray, p, &wall.final_dist, 0);
		call_wall(cubed, &wall, ray, flag);
	}
	render_doors(cubed, &wall);
}
