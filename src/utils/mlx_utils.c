/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:58:47 by nromito           #+#    #+#             */
/*   Updated: 2024/08/02 16:20:45 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	draw_shape(t_img *img, double x, double y, int size, int color)
{
	int	i;
	int	j;
	int	start_x;
	
	start_x = x;
	j = -1;
	while (++j < size)
	{
		i = -1;
		x = start_x;
		while (++i < size)
		{
			better_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	better_pixel_put(t_img *img, int x, int y, int color)
{
	int offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	if (offset < 0 || offset > WIDTH * HEIGHT * 4)
		return ;
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}

void	create_img(void *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->pixel_ptr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);	
}

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color) {
    int dx;
    int sx;
    int dy;
    int sy;
    int err;

    sx = x0 < x1 ? 1 : -1;
    dy = - abs(y1 - y0);
    sy = y0 < y1 ? 1 : -1;
    dx = abs(x1 - x0);
    err = dx + dy;
    while (1)
    {
        better_pixel_put(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
