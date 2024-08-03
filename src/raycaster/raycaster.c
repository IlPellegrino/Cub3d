/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/08/03 19:06:10 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void render_doors(t_cubed *cubed, t_wall *wall)
{
	t_player *p;
	t_raycast *ray;
	int map_w;
	int map_h;

	ray = cubed->raycast;
	p = cubed->player;
	map_h = cubed->game->ht;
    double half_fov = cubed->settings->radians_fov / 2;
    double half_screen = WIDTH / 2;
    for (ray->r = 0; ray->r < WIDTH; ray->r++)
    {
        double ray_angle = p->angle + atan((ray->r - half_screen) / half_screen * tan(half_fov));

    // Normalize the angle
        ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
        ray->ra = ray_angle;
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
            if (mapY < 0)
                mapY = 0;
            if (mapY >= map_h)
                mapY = map_h - 1;
            map_w = ft_strlen(cubed->map[mapY]);
    
            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && (cubed->map[mapY][mapX] == 'A' || cubed->map[mapY][mapX] == 'D' || cubed->map[mapY][mapX] == '1'))
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
            if (mapY < 0)
                mapY = 0;
            if (mapY >= map_h)
                mapY = map_h - 1;
            map_w = ft_strlen(cubed->map[mapY]);
            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && (cubed->map[mapY][mapX] == 'A' || cubed->map[mapY][mapX] == 'D' || cubed->map[mapY][mapX] == '1'))
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

        int color;
        // Select the closest hit
        double distH = sqrt((p->x - horX) * (p->x - horX) + (p->y - horY) * (p->y - horY));
        double distV = sqrt((p->x - verX) * (p->x - verX) + (p->y - verY) * (p->y - verY));
        
        double finalDist;
        if (distH < distV)
        {
            if (ray->ra > 0 && ray->ra < PI)
                color = 5; // north
            else
                color = 5; //south
            ray->rx = horX;
            ray->ry = horY;
            finalDist = distH;
        }
        else
        {
            if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
                color = 4; // east
            else
                color = 4; //west
            ray->rx = verX;
            ray->ry = verY;
            finalDist = distV;
        }
        //draw_line(cubed->img, p->x, p->y, ray->rx, ray->ry, red);
        // Correct the distance for the fish-eye effect
        double correctedDist = finalDist * cos(ray_angle - p->angle);

        // Calculate wall height
        wall->wall_height = (TILE_SIZE * HEIGHT) / correctedDist;

        wall->wall_top = (HEIGHT / 2) - (wall->wall_height / 2);
        wall->wall_bottom = wall->wall_top + wall->wall_height;
        if (wall->wall_bottom > HEIGHT)
            wall->wall_bottom = HEIGHT;
        if (wall->wall_top < 0)
            wall->wall_top = 0;
        int    i;
        int    j;

        i = (int)(ray->rx / TILE_SIZE);
        j = (int)(ray->ry / TILE_SIZE);
        if (i >= 0 && i < map_w && j >= 0 && j < map_h && (cubed->map[j][i] == 'A' || cubed->map[j][i] == 'D'))
            draw_walls(cubed, wall, color);
    }
}

void rendering(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    int map_h = cubed->game->ht;
    int map_w;
    double half_fov = cubed->settings->radians_fov / 2;
    double half_screen = WIDTH / 2;
    t_wall wall;

    //double initial_angle = p->angle - (RADIANS_FOV / 2);
    for (ray->r = 0; ray->r < WIDTH; ray->r++)
    {
        double ray_angle = p->angle + atan((ray->r - half_screen) / half_screen * tan(half_fov));

    // Normalize the angle
        ray_angle = fmod(ray_angle + 2 * PI, 2 * PI);
        ray->ra = ray_angle;
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
            if (mapY < 0)
                mapY = 0;
            if (mapY >= map_h)
                mapY = map_h - 1;
            map_w = ft_strlen(cubed->map[mapY]);
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
        double distH = sqrt((p->x - horX) * (p->x - horX) + (p->y - horY) * (p->y - horY));
        double distV = sqrt((p->x - verX) * (p->x - verX) + (p->y - verY) * (p->y - verY));
        
        double finalDist;
        if (distH < distV)
        {
            if (ray->ra > 0 && ray->ra < PI)
                flag = 0; // north
            else
                flag = 1; // south
            ray->rx = horX;
            ray->ry = horY;
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
        double correctedDist = finalDist * cos(ray_angle - p->angle);

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
