/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:09:04 by hbecki            #+#    #+#             */
/*   Updated: 2022/03/25 19:56:14 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*pointer_s;
	unsigned int	i;
	unsigned int	e;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	e = (ft_strlen(s1) + ft_strlen(s2) + 1);
	pointer_s = (char *)malloc(e * sizeof(char));
	if (pointer_s == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		pointer_s[i] = (char)s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		pointer_s[i] = (char)s2[i - ft_strlen(s1)];
		i++;
	}
	pointer_s[i] = '\0';
	return (pointer_s);
}
