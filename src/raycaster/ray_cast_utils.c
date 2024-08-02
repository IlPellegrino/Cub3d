/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:02:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/02 22:09:40 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void    hor_inters(t_cubed *cubed, double aTan)
{
      double horStepX, horStepY;
        t_player *p = cubed->player;
        t_raycast *ray = cubed->raycast;
        int map_w;
        ray->dof = 0;
        if (ray->ra > PI)
        {
            ray->horY = (((int)p->y / TILE_SIZE) * TILE_SIZE) - 0.0001;
            ray->horX = (p->y - ray->horY) * aTan + p->x;
            horStepY = -TILE_SIZE;
            horStepX = -horStepY * aTan;
        }
        else if (ray->ra < PI)
        {
            ray->horY = (((int)p->y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            ray->horX = (p->y - ray->horY) * aTan + p->x;
            horStepY = TILE_SIZE;
            horStepX = -horStepY * aTan;
        }
        else
        {
            ray->horX = p->x;
            ray->horY = p->y;
            ray->dof = cubed->game->ht;
        }

        while (ray->dof < cubed->game->ht)
        {
            int mapX = (int)(ray->horX) / TILE_SIZE;
            int mapY = (int)(ray->horY) / TILE_SIZE;
            if (mapY < 0)
                mapY = 0;
            if (mapY >= cubed->game->ht)
                mapY = cubed->game->ht - 1;
            map_w = ft_strlen(cubed->map[mapY]);
            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < cubed->game->ht && cubed->map[mapY][mapX] == '1')
            {
                ray->hx = ray->horX;
                ray->hy = ray->horY;
                ray->dof = cubed->game->ht;
            }
            else
            {
                ray->horX += horStepX;
                ray->horY += horStepY;
                ray->dof += 1;
            }
        }
}
