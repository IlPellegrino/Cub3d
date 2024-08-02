/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:54:57 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/02 15:02:38 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

int	key_press(int pressed, t_keys *key)
{
	if (pressed == w)
		key->w = 1;
	else if (pressed == s)
		key->s = 1;
	else if (pressed == a)
		key->a = 1;
	else if (pressed == d)
		key->d = 1;
	else if (pressed == left)
		key->left = 1;
	else if (pressed == right)
		key->right = 1;
	else if (pressed == esc)
		key->esc = 1;
	else if (pressed == p && key->pause == 0)
		key->pause = 1;
	else if (pressed == p && key->pause)
		key->pause = 0;
	else if (pressed == space)
		key->space = 1;
	else if (pressed == plus)
		key->plus = 1;
	else if (pressed == minus)
		key->minus = 1;
	return (0);
}

int	key_release(int realesed, t_keys *key)
{
	if (realesed == w)
		key->w = 0;
	else if (realesed == s)
		key->s = 0;
	else if (realesed == a)
		key->a = 0;
	else if (realesed == d)
		key->d = 0;
	else if (realesed == left)
		key->left = 0;
	else if (realesed == right)
		key->right = 0;
	else if (key->esc)
		key->esc = 0;
	else if (realesed == minus)
		key->minus = 0;
	else if (realesed == plus)
		key->plus = 0;
	//printf("release\n");
	return (1);
}
