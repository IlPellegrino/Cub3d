/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/07/21 16:53:54 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

#define FOV (60 * (PI / 180)) // Field of view in radians
#define NUM_RAYS 1080 // Number of rays to cast (resolution of the rendering)

void draw_vertical_line(t_img *img, int x, int start, int end, int color)
{
    for (int y = start; y < end; y++)
    {
        better_pixel_put(img, x, y, color);
    }
}

void drawRays3D(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    int map_w = 44;
    int map_h = matrix_len(cubed->map);
    double angle_step = FOV / NUM_RAYS;
    double ray_angle = p->angle - (FOV / 2);

    for (int r = 0; r < NUM_RAYS; r++, ray_angle += angle_step)
    {
        ray->ra = fmod(ray_angle, 2 * PI);
        if (ray->ra < 0) ray->ra += 2 * PI;
        
        ray->dof = 0;
        double aTan = -1 / tan(ray->ra);

        // Calculate horizontal intersection
        double horX, horY, horStepX, horStepY;
        ray->dof = 0;
        if (ray->ra > PI)
        {
            horY = (((int)p->y / TILE_SIZE) * TILE_SIZE) - 0.0001;
            horX = (p->y - horY) * aTan + p->x;
            horStepY = -TILE_SIZE;
            horStepX = -horStepY * aTan;
        }
        else if (ray->ra < PI)
        {
            horY = (((int)p->y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
            horX = (p->y - horY) * aTan + p->x;
            horStepY = TILE_SIZE;
            horStepX = -horStepY * aTan;
        }
        else
        {
            horX = p->x;
            horY = p->y;
            ray->dof = map_h;
        }

        while (ray->dof < map_h)
        {
            int mapX = (int)(horX) / TILE_SIZE;
            int mapY = (int)(horY) / TILE_SIZE;

            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && cubed->map[mapY][mapX] == '1')
            {
                ray->hx = horX;
                ray->hy = horY;
                ray->dof = map_h;
            }
            else
            {
                horX += horStepX;
                horY += horStepY;
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

        // Select the closest hit
        double distH = sqrt((p->x - horX) * (p->x - horX) + (p->y - horY) * (p->y - horY));
        double distV = sqrt((p->x - verX) * (p->x - verX) + (p->y - verY) * (p->y - verY));
        
        double finalDist;
        if (distH < distV)
        {
            ray->rx = horX;
            ray->ry = horY;
            finalDist = distH;
        }
        else
        {
            ray->rx = verX;
            ray->ry = verY;
            finalDist = distV;
        }

        //draw_line(cubed->img, p->x, p->y, ray->rx, ray->ry, red);
        // Correct the distance for the fish-eye effect
        double correctedDist = finalDist * cos(p->angle - ray->ra);

        // Calculate wall height
        int wallHeight = (TILE_SIZE * HEIGHT) / correctedDist;

        // Ensure wall height does not exceed the screen height
        if (wallHeight > HEIGHT) {
            wallHeight = HEIGHT;
        }

        // Calculate start and end positions for the wall slice
        int wallTop = (HEIGHT / 2) - (wallHeight / 2);
        int wallBottom = wallTop + wallHeight;

        // Draw the wall slice (a vertical line) on the screen
        // draw top half of the screen as the ceiling
        draw_vertical_line(cubed->img, r, 0, wallTop, cyan);
        // draw bottom half of the scree as floor
        draw_vertical_line(cubed->img, r, wallBottom, HEIGHT, brown);
        draw_vertical_line(cubed->img, r, wallTop, wallBottom, pastel);
        
    }
}
