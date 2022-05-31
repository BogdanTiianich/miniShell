/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:41:18 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	symbol;

	i = 0;
	str = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == symbol)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
