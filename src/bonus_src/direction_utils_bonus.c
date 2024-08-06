/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:26:17 by nromito           #+#    #+#             */
/*   Updated: 2024/08/05 16:17:13 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	d_flag(t_raycast *ray, double h_dist, double v_dist, double *f_dist)
{
	int	flag;

	if (h_dist < v_dist)
	{
		if (ray->ra > 0 && ray->ra < PI)
			flag = 5;
		else
			flag = 5;
		ray->rx = ray->hor_x;
		ray->ry = ray->hor_y;
		*(f_dist) = h_dist;
	}
	else
	{
		if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
			flag = 4;
		else
			flag = 4;
		ray->rx = ray->ver_x;
		ray->ry = ray->ver_y;
		*(f_dist) = v_dist;
	}
	return (flag);
}

int	w_flag(t_raycast *ray, double h_dist, double v_dist, double *f_dist)
{
	int	flag;

	if (h_dist < v_dist)
	{
		if (ray->ra > 0 && ray->ra < PI)
			flag = 1;
		else
			flag = 0;
		ray->rx = ray->hor_x;
		ray->ry = ray->hor_y;
		*(f_dist) = h_dist;
	}
	else
	{
		if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
			flag = 3;
		else
			flag = 2;
		ray->rx = ray->ver_x;
		ray->ry = ray->ver_y;
		*(f_dist) = v_dist;
	}
	return (flag);
}

int	calculate_dir(t_raycast *ray, t_player *p, double *f_dist, int flag)
{
	double	h_dist;
	double	v_dist;

	h_dist = sqrt((p->x - ray->hor_x) * (p->x - ray->hor_x)
			+ (p->y - ray->hor_y) * (p->y - ray->hor_y));
	v_dist = sqrt((p->x - ray->ver_x) * (p->x - ray->ver_x)
			+ (p->y - ray->ver_y) * (p->y - ray->ver_y));
	if (flag)
		flag = d_flag(ray, h_dist, v_dist, f_dist);
	else
		flag = w_flag(ray, h_dist, v_dist, f_dist);
	return (flag);
}
