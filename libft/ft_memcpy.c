/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:39:06 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:51 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	const char	*src_in;
	char		*dst_in;
	size_t		i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	dst_in = (char *)dst;
	src_in = (const char *)src;
	while (i < n)
	{
		dst_in[i] = src_in[i];
		i++;
	}
	return (dst);
}
