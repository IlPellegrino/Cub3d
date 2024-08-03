/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:00:31 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 16:01:24 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

static void	update_position(int d_pos[2], int s_pos[2], int start[2], int *err)
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= d_pos[1])
	{
		*err += d_pos[1];
		start[0] += s_pos[0];
	}
	if (e2 <= d_pos[0])
	{
		*err += d_pos[0];
		start[1] += s_pos[1];
	}
}

static int	init_vars(int start[2], int end[2], int s_pos[2], int d_pos[2])
{
	int	err;

	if (start[0] < end[0])
		s_pos[0] = 1;
	else
		s_pos[0] = -1;
	d_pos[1] = -abs(end[1] - start[1]);
	if (start[1] < end[1])
		s_pos[1] = 1;
	else
		s_pos[1] = -1;
	d_pos[0] = abs(end[0] - start[0]);
	err = d_pos[0] + d_pos[1];
	return (err);
}

void	draw_line(t_img *img, int start_pos[2], int x1, int y1)
{
	int	s_pos[2];
	int	d_pos[2];
	int	end_pos[2];
	int	err;

	end_pos[1] = y1;
	end_pos[0] = x1;
	err = init_vars(start_pos, end_pos, s_pos, d_pos);
	while (1)
	{
		better_pixel_put(img, start_pos[0], start_pos[1], black_coral);
		if (start_pos[0] == x1 && start_pos[1] == y1)
			break ;
		update_position(d_pos, s_pos, start_pos, &err);
	}
}
