/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <cristianiusca13@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:45:44 by ciusca            #+#    #+#             */
/*   Updated: 2023/10/30 20:57:54 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stddef.h>

int	n_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i ++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	cifra;
	int		len;

	cifra = n;
	len = n_len(cifra);
	str = (char *) malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	len -= 1;
	if (cifra < 0)
	{
		cifra *= -1;
		str[0] = '-';
	}
	if (cifra == 0)
		str[0] = '0';
	str[len + 1] = 0;
	while (cifra > 0)
	{
		str[len] = cifra % 10 + 48;
		cifra /= 10;
		len --;
	}
	return (str);
}
