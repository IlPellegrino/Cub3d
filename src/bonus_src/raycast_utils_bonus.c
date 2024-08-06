/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:02:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/05 16:19:07 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	call_wall(t_cubed *cubed, t_wall *wall, t_raycast *ray, int flag)
{
	t_player	*p;
	double		corrected_dist;

	p = cubed->player;
	corrected_dist = wall->final_dist * cos(ray->ray_angle - p->angle);
	wall->wall_height = (TILE_SIZE * HEIGHT) / corrected_dist;
	wall->wall_top = (HEIGHT / 2) - (wall->wall_height / 2);
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	wall->wall_bottom = wall->wall_top + wall->wall_height;
	if (wall->wall_bottom > HEIGHT)
		wall->wall_bottom = HEIGHT;
	draw_vertical_line(cubed, 0, wall->wall_top, cubed->game->ceiling_cl);
	draw_vertical_line(cubed, wall->wall_bottom, HEIGHT, cubed->game->floor_cl);
	draw_walls(cubed, wall, flag);
}

void	call_door_wall(t_cubed *cubed, t_wall *wall, t_raycast *ray, int flag)
{
	int	i;
	int	j;

	i = (int)(ray->rx / TILE_SIZE);
	j = (int)(ray->ry / TILE_SIZE);
	wall->wall_top = (HEIGHT / 2) - (wall->wall_height / 2);
	wall->wall_bottom = wall->wall_top + wall->wall_height;
	if (wall->wall_bottom > HEIGHT)
		wall->wall_bottom = HEIGHT;
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	if (i >= 0 && i < cubed->map_w && j >= 0 && j < cubed->game->ht
		&& is_door(cubed, i, j))
		draw_walls(cubed, wall, flag);
}

void	angle_ray(t_raycast *ray, t_player *p)
{
	ray->ray_angle = p->angle + atan((ray->r - ray->half_screen)
			/ ray->half_screen * tan(ray->half_fov));
	ray->ray_angle = fmod(ray->ray_angle + 2 * PI, 2 * PI);
	ray->ra = ray->ray_angle;
	ray->dof = 0;
	ray->a_tan = -1 / tan(ray->ra);
}

int	is_door(t_cubed *cubed, int map_x, int map_y)
{
	if (cubed->map[map_y][map_x] == 'D'
		|| cubed->map[map_y][map_x] == 'A')
		return (1);
	return (0);
}
