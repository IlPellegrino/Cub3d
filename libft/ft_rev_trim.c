/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:54:33 by nromito           #+#    #+#             */
/*   Updated: 2024/07/20 23:56:53 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cinstr(const char *str, const char c);

char	*ft_rev_trim(const char *s1, const char *set)
{
	char	*newstr;
	size_t	i;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	while (i > 0 && ft_cinstr(set, s1[i - 1]))
		i--;
	newstr = malloc(sizeof(char) * (i + 1));
	if (newstr == NULL)
		return (NULL);
	newstr[i] = '\0';
	while (i > 0)
	{
		newstr[i - 1] = s1[i - 1];
		i--;
	}
	return (newstr);
}

static int	ft_cinstr(const char *str, const char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}