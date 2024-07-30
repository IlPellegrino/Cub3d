/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:07:38 by nromito           #+#    #+#             */
/*   Updated: 2024/07/30 18:08:57 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void draw_vertical_line(t_cubed *cubed, int start, int end, int color)
{
	int	y;

	y = start;
    while (y < end)
    {
        better_pixel_put(cubed->img, cubed->raycast->r, y, color);
		y++;
    }
}

void	y_loop(t_cubed *cubed, t_wall *wall, t_img *texture)
{
	int	y;
	int	tex_y;
	int	color_idx;
	int	tex_color;

	y = wall->wall_top;
	while (y < wall->wall_bottom)
	{
		tex_y = (int)wall->tex_pos % texture->h;
		wall->tex_pos += wall->tex_step;
		color_idx = tex_y * texture->w + wall->tex_x;
		if (color_idx >= 0 && color_idx < texture->w * texture->h)
		{
			tex_color = texture->data[color_idx];
			if (tex_color != black)
				better_pixel_put(cubed->img, cubed->raycast->r, y, tex_color);
		}
		y++;
	}
}

void draw_walls(t_cubed *cubed, t_wall *wall, int flag)
{
    t_img	*texture;

    // Determine which texture to use based on the color
    if (flag == 0)
        texture = &cubed->texture[0];
    else if (flag == 1)
        texture = &cubed->texture[1];
    else if (flag == 2)
        texture = &cubed->texture[2];
    else if (flag == 3)
        texture = &cubed->texture[3];
    else
        texture = &cubed->texture[4];
    // Calculate the x coordinate on the texture
    if (flag == 2 || flag == 3)
    	wall->tex_x = (int)cubed->raycast->ry % TILE_SIZE;
	else
		wall->tex_x = (int)cubed->raycast->rx % TILE_SIZE;
    wall->tex_x = (wall->tex_x * texture->w) / TILE_SIZE;
    wall->tex_x = wall->tex_x % texture->w;
    wall->tex_step = (double)texture->h / wall->wall_height;
    wall->tex_pos = (wall->wall_top - HEIGHT / 2
		+ wall->wall_height / 2) * wall->tex_step;
	y_loop(cubed, wall, texture);
}
