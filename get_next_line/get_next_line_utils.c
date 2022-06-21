/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:01:07 by snuts             #+#    #+#             */
/*   Updated: 2022/04/03 19:25:31 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strlen_n(char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc (sizeof(char) * (ft_strlen_n(s1)
				+ ft_strlen_n(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
		str[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		str[k++] = s2[i++];
	str[k] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

char	*ft_substr_n(char *s, int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	j;

	i = start;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (len > (size_t) ft_strlen_n(s + start))
		len = (size_t) ft_strlen_n(s + start);
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && start < ft_strlen_n(s) && j < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*rem_swap(char *rem, int check)
{
	char	*mem;

	mem = ft_substr_n(rem, check + 1, ft_strlen_n(rem) - check);
	free(rem);
	rem = NULL;
	rem = ft_substr_n(mem, 0, ft_strlen_n(mem));
	free(mem);
	mem = NULL;
	if (ft_strlen_n(rem) == 0)
	{
		free (rem);
		rem = NULL;
	}
	return (rem);
}
