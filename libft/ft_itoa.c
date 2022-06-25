/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:11:28 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:13 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_itoa_helper(int n, char *s, int i, int NUM)
{
	if ((n / 10) * i > 0)
	{
		NUM = ft_itoa_helper(n / 10, s, i, NUM);
	}
	if ((i == -1) && !((n / 10) * i > 0))
	{
		s[0] = '-';
		NUM++;
	}
	s[NUM] = (n % 10) * i + '0';
	NUM++;
	return (NUM);
}

int static	ft_itoa_length(int n, int i, int NUM)
{
	if ((n / 10) * i > 0)
	{
		NUM = ft_itoa_length(n / 10, i, NUM);
	}
	if ((i == -1) && !((n / 10) * i > 0))
	{
		NUM++;
	}
	NUM++;
	return (NUM);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 1;
	if (n < 0)
		i = -1;
	str = (char *)malloc((ft_itoa_length(n, i, 0) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[ft_itoa_helper(n, str, i, 0)] = '\0';
	return (str);
}
