/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:19:29 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 17:23:15 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	events(int key, t_cubed *cubed)
{
	printf("key = %d\n", key);
	if (key == esc)
		ft_close(cubed, 0);
	return (1);
}