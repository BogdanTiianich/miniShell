/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:45:15 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 23:19:59 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t		i;
	size_t		dst_len;
	const char	*src_in;
	char		*dst_in;

	src_in = (const char *)src;
	dst_in = (char *)dst;
	i = 0;
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen((char *)src));
	while ((i < dstsize - dst_len - 1) && (src_in[i] != '\0'))
	{
		dst_in[dst_len + i] = src_in[i];
		i++;
	}
	dst_in[i + dst_len] = '\0';
	return (dst_len + ft_strlen((char *)src));
}
