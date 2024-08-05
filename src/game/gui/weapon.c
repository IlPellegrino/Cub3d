/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:32:47 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/05 19:27:33 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

void	show_weapon(t_cubed *cubed)
{
	t_img	*weapon;
	int		i;
	int		j;

	weapon = &cubed->weapon[0];
	weapon->data = (int *)mlx_get_data_addr(weapon->img,
			&weapon->bits_per_pixel, &weapon->line_len, &weapon->endian);
	i = -1;
	while (++i < weapon->h)
	{
		j = -1;
		while (++j < weapon->w)
		{
			if (weapon->data[i * weapon->line_len / 4 + j] != (int)0xff000000)
				better_pixel_put(cubed->img, j + 650, i + 115,
					weapon->data[i * weapon->line_len / 4 + j]);
		}
	}
}
