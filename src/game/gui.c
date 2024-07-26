/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:22:45 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/27 00:27:44 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	text_gui(t_cubed *cubed)
{
	if (cubed->gui->open_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15, HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO OPEN DOOR");
	else if (cubed->gui->close_door)
		mlx_string_put(cubed->mlx, cubed->win, WIDTH / 2 + 15, HEIGHT / 2 - 5, white, "PRESS 'SPACE' TO CLOSE DOOR");

}