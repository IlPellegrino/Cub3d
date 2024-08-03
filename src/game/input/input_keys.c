/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:54:57 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 16:42:20 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cubed.h"

void	gui_keys(int pressed, t_keys *key)
{
	if (pressed == p && key->pause == 0)
		key->pause = 1;
	else if (pressed == p && key->pause)
		key->pause = 0;
	else if (pressed == space)
		key->space = 1;
	else if (pressed == plus)
		key->plus = 1;
	else if (pressed == minus)
		key->minus = 1;
	else if (pressed == shift)
		key->shift = 1;
}

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
	else if (pressed == page_up)
		key->page_up = 1;
	else if (pressed == page_down)
		key->page_down = 1;
	else
		gui_keys(pressed, key);
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
	else if (realesed == shift)
		key->shift = 0;
	else if (realesed == page_up)
		key->page_up = 0;
	else if (realesed == page_down)
		key->page_down = 0;
	return (1);
}
