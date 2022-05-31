/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:51:31 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/19 22:44:40 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*pointer;
	unsigned int	i;
	unsigned int	l;

	l = 0;
	if (start < 0 || s == NULL)
		return (NULL);
	if (start > ft_strlen(s) - 1)
		start = ft_strlen(s);
	else if (ft_strlen(s) - start > len)
		l = 1;
	i = start;
	pointer = (char *)malloc(((ft_strlen(s) - start) * \
	(1 - l) + 1 + len * l) * sizeof(char));
	if (pointer == NULL)
		return (NULL);
	while ((i < start + len) && ((char)s[i] != '\0'))
	{
		pointer[i - start] = (char)s[i];
		i++;
	}
	pointer[i - start] = '\0';
	return (pointer);
}
