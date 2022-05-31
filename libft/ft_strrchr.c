/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:27:50 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/19 22:43:46 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pointer;
	char	*buf;
	int		j;

	buf = (char *)s;
	j = ft_strlen(buf);
	while (j >= 0)
	{
		if (buf[j] == (char)c)
		{
			pointer = &buf[j];
			return (pointer);
		}
		j--;
	}
	return (NULL);
}
