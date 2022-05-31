/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:43:17 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:48 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*pointer_s1;
	unsigned char	*pointer_s2;

	i = 0;
	pointer_s2 = (unsigned char *)s2;
	pointer_s1 = (unsigned char *)s1;
	while (i < n)
	{
		if (pointer_s1[i] != pointer_s2[i])
		{
			return (pointer_s1[i] - pointer_s2[i]);
		}
		i++;
	}
	return (0);
}
