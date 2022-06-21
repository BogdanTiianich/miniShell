/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:40:52 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/17 15:23:13 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_status(int status)
{
	int	k;

	k = 0;
	if (status == 0)
		return (1);
	while (status != 0)
	{
		status = status / 10;
		++k;
	}
	return (k);
}

void	ft_itoan(char *dst, int status, int *j)
{
	char	x[10];
	int		i;

	i = 0;
	while (status != 0)
	{
		x[i++] = (status % 10) + '0';
		status = status / 10;
	}
	while (i != 0)
		dst[(*j)++] = x[--i];
}

int	ft_strlens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (++i);
}

int	is_not_word(int x)
{
	if (x < 48)
		return (1);
	else if (x > 90 && x < 97)
	{
		if (x != 95)
			return (1);
	}
	else if (x > 122 && x <= 127)
		return (1);
	else if (x > 57 && x < 65)
		return (1);
	return (0);
}

int	ft_strcmp_v2(char *cmp, char *str)
{
	int	i;

	i = 0;
	while (str[i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (!cmp[i] && (is_not_word(str[i]) || str[i] == '$'))
		return (1);
	return (0);
}
