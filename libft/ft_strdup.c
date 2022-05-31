/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 20:16:46 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:27:21 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*pointer;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	pointer = (char *)malloc((len + 1) * sizeof(char));
	if (pointer == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		pointer[i] = s1[i];
		i++;
	}
	pointer[i] = '\0';
	return (pointer);
}
