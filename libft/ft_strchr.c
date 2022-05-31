/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:00:38 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/18 17:43:00 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*pointer;
	char	*buf;

	i = 0;
	buf = (char *)s;
	while (buf[i] != '\0')
	{
		if (buf[i] == (char)c)
		{
			pointer = &buf[i];
			return (pointer);
		}
		i++;
	}
	if (c == 0)
	{
		pointer = &buf[i];
		return (pointer);
	}
	return (NULL);
}
