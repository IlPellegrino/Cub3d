/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:13 by nromito           #+#    #+#             */
/*   Updated: 2024/07/23 14:23:14 by nromito          ###   ########.fr       */
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

void draw_walls(t_cubed *cubed, int x, int start, int end, double wall_height, int color)
{
    t_img *texture;
    int     tex_x;
    int     tex_y;
    double  tex_step;
    double  tex_pos;

    // Determine which texture to use based on the color
    switch (color) {
        case yellow:
            texture = &cubed->texture[0]; // North
            break;
        case blue:
            texture = &cubed->texture[1]; // South
            break;
        case red:
            texture = &cubed->texture[2]; // East
            break;
        case green:
            texture = &cubed->texture[3]; // West
            break;
        // default:
        //     // Default texture (if needed)
        //     texture = &cubed->texture[0];
        //     break;
    }

    // Calculate the x coordinate on the texture
    // Determine tex_x based on wall side and ray position
    if (color == red || color == green) 
    {
        // For vertical walls (East or West)
        tex_x = (int)(cubed->raycast->ry) % TILE_SIZE;
    }
    else 
    {
        // For horizontal walls (North or South)
        tex_x = (int)(cubed->raycast->rx) % TILE_SIZE;
    }


    // Normalize tex_x to be within the texture width
    if (tex_x < 0)
        tex_x += TILE_SIZE; // Ensure positive value
    tex_x = (tex_x * texture->w) / TILE_SIZE;

    tex_step = (double)texture->h / (wall_height);
    tex_pos = (start - HEIGHT / 2 + wall_height / 2) * tex_step;
    printf("tex pos = %f\n", tex_pos);
	printf("tex step = %f\n", tex_step);

    for (int y = start; y < end; y++)
    {
        tex_pos += tex_step / 2;
        tex_y = (int)tex_pos % texture->h;
		// printf("AFTER pos = %f\n", tex_pos);
		// printf("AFTER step = %f\n", tex_step);

        // Calculate the color index
        int color_idx = tex_y * texture->w + tex_x;

        // Ensure color_idx is within the bounds of the texture data array
        if (color_idx > 0 && color_idx < texture->w * texture->h)
        {
            // Get the color from the texture data
            int tex_color = texture->data[color_idx];

            // Put the pixel on the screen
            better_pixel_put(cubed->img, x, y, tex_color);
        }
    }
}



void rendering(t_cubed *cubed)
{
    t_player *p = cubed->player;
    t_raycast *ray = cubed->raycast;
    int map_w = 44;
    int map_h = matrix_len(cubed->map);
    double angle_step = RADIANS_FOV / WIDTH;
    double ray_angle = p->angle - (RADIANS_FOV / 2);

    for (int r = 0; r < WIDTH; r++, ray_angle += angle_step)
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
                color = green; //ovest
            ray->rx = verX;
            ray->ry = verY;
            finalDist = distV;
        }

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
        // draw bottom half of the screen as floor
        draw_vertical_line(cubed->img, r, wallBottom, HEIGHT, brown);
        draw_walls(cubed, r, wallTop, wallBottom, wallHeight, color);
    }
}
