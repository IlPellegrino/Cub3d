/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/07/27 01:38:53 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void draw_vertical_line(t_img *img, int x, int start, int end, int color)
{
    for (int y = start; y < end; y++)
    {
        better_pixel_put(img, x, y, color);
    }
}

void draw_walls(t_cubed *cubed, int start, int end, double wall_height, int flag) {
    t_img *texture;
    int     tex_x;
    int     tex_y;
    double  tex_step;
    double  tex_pos;

    // Determine which texture to use based on the color
    if (flag == yellow)
        texture = &cubed->texture[0];
    else if (flag == blue)
        texture = &cubed->texture[1];
    else if (flag == red)
        texture = &cubed->texture[2];
    else if (flag == green)
        texture = &cubed->texture[3];
    else
        texture = &cubed->texture[4];

    // Calculate the x coordinate on the texture
    tex_x = (int)(flag == red || flag == green ? cubed->raycast->ry : cubed->raycast->rx) % TILE_SIZE;
    tex_x = (tex_x * texture->w) / TILE_SIZE;
    tex_x = tex_x % texture->w;

    tex_step = (double)texture->h / wall_height;
    tex_pos = (start - HEIGHT / 2 + wall_height / 2) * tex_step;

    for (int y = start; y < end; y++) {
        tex_y = (int)tex_pos % texture->h;
        tex_pos += tex_step;

        int color_idx = tex_y * texture->w + tex_x;

        if (color_idx >= 0 && color_idx < texture->w * texture->h) {
            int tex_color = texture->data[color_idx];
            if (tex_color != black)
                better_pixel_put(cubed->img, cubed->raycast->r, y, tex_color);
        }
    }
}

void render_doors(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    int map_h = cubed->game->ht;
    int map_w;
    double angle_step = RADIANS_FOV / WIDTH;
    double initial_angle = p->angle - (RADIANS_FOV / 2);
    
    for (ray->r = 0; ray->r < WIDTH; ray->r++)
    {
        double ray_angle = initial_angle + ray->r * angle_step;
        if (ray_angle < 0) ray_angle += 2 * PI;
        if (ray_angle >= 2 * PI) ray_angle -= 2 * PI;

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
            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && cubed->map[mapY][mapX] == 'D')
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
            if (mapX >= 0 && mapX < map_w && mapY >= 0 && mapY < map_h && (cubed->map[mapY][mapX] == 'D'))
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
                color = purple; // north
            else
                color = purple; //south
            ray->rx = horX;
            ray->ry = horY;
            finalDist = distH;
        }
        else
        {
            if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
                color = purple; // east
            else
                color = purple; //west
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


        // Calculate start and end positions for the wall slice
        int wallTop = (HEIGHT / 2) - (wallHeight / 2);
        int wallBottom = wallTop + wallHeight;
        if (wallBottom > HEIGHT)
        {
            wallBottom = HEIGHT;
        }
        if (wallTop < 0)
        {
            wallTop = 0;
        }

        // Draw the wall slice (a vertical line) on the screen
        // draw top half of the screen as the ceiling
        //draw_vertical_line(cubed->img, ray->r, 0, wallTop, cyan);
        // draw bottom half of the screen as floor
        //draw_vertical_line(cubed->img, ray->r, wallBottom, HEIGHT, brown);
        int    i;
        int     j;

        i = (int)(ray->rx / TILE_SIZE);
        j = (int)(ray->ry / TILE_SIZE);
        if (i >= 0 && i < map_w && j >= 0 && j < map_h && cubed->map[j][i] == 'D')
            draw_walls(cubed, wallTop, wallBottom, wallHeight, color);
        
    }
}

void rendering(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    int map_h = cubed->game->ht;
    int map_w;
    double initial_angle = p->angle - (RADIANS_FOV / 2);
    for (ray->r = 0; ray->r < WIDTH; ray->r++)
    {
        double ray_angle = initial_angle + ray->r * ANGLE_STEP;
        if (ray_angle < 0) ray_angle += 2 * PI;
        if (ray_angle >= 2 * PI) ray_angle -= 2 * PI;

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
            map_w = ft_strlen(cubed->map[mapY]);
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

        int color;
        // Select the closest hit
        double distH = sqrt((p->x - horX) * (p->x - horX) + (p->y - horY) * (p->y - horY));
        double distV = sqrt((p->x - verX) * (p->x - verX) + (p->y - verY) * (p->y - verY));
        
        double finalDist;
        if (distH < distV)
        {
            if (ray->ra > 0 && ray->ra < PI)
                color = yellow; // north
            else
                color = blue; //south
            ray->rx = horX;
            ray->ry = horY;
            finalDist = distH;
        }
        else
        {
            if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
                color = red; // east
            else
                color = green; //west
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


        // Calculate start and end positions for the wall slice
        int wallTop = (HEIGHT / 2) - (wallHeight / 2);
        int wallBottom = wallTop + wallHeight;
        if (wallBottom > HEIGHT)
        {
            wallBottom = HEIGHT;
        }
        if (wallTop < 0)
        {
            wallTop = 0;
        }

        // Draw the wall slice (a vertical line) on the screen
        // draw top half of the screen as the ceiling
        draw_vertical_line(cubed->img, ray->r, 0, wallTop, cyan);
        // draw bottom half of the screen as floor
        draw_vertical_line(cubed->img, ray->r, wallBottom, HEIGHT, brown);
        draw_walls(cubed, wallTop, wallBottom, wallHeight, color);
    }
      render_doors(cubed);
}