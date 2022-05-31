/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:44:11 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:24:31 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int static	ft_atoi_help(const char *s, int *ngtv, int *i)
{
	int	a;

	*i = 0;
	*ngtv = 0;
	while (((s[*i] == 32) || (s[*i] == 9) || ((s[*i] >= 10) \
	&& (s[*i] <= 13))) && (s[*i] != '\0'))
		(*i)++;
	if (((s[*i] == '-') || (s[*i] == '+')) && (s[*i] != '\0'))
	{
		if (s[*i] == '-')
			(*ngtv)++;
		(*i)++;
	}
	a = *i + *ngtv - *i;
	return (a);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	result;
	int	ngtv;
	int	count;

	result = 0;
	count = 0;
	ngtv = ft_atoi_help(s, &ngtv, &i);
	while (((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		count++;
		result = result * 10 + s[i] - '0';
		i++;
	}
	if (count >= 19)
		return (-1 * (1 - ngtv));
	if (ngtv % 2 != 0)
		result *= -1;
	return (result);
}
