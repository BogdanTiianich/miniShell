/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:07:15 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/19 22:42:57 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*haystack;

	j = 0;
	haystack = (char *)hay;
	if (ft_strlen(needle) == 0)
		return (haystack);
	while ((j < len) && (haystack[j] != '\0'))
	{
		i = 0;
		while ((needle[i] != '\0') && (j + i < len))
		{
			if (ft_isascii((needle[i])) == 0)
				return (haystack);
			if (needle[i] != haystack[j + i])
				break ;
			i++;
		}
		if (i == ft_strlen(needle))
			return (&haystack[j]);
		j++;
	}
	return (NULL);
}
