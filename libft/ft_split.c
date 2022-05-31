/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:19:02 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/19 22:47:38 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void static	ft_clear(char ***arr_str, int i)
{
	while (i > 0)
	{
		i--;
		free(*arr_str[i]);
	}
	free(*arr_str);
}

int	static	num_of_strings(char const *s, char c, int *start)
{
	int	i;
	int	num_of_strings;
	int	k;

	i = 0;
	num_of_strings = 0;
	if (ft_strlen(s) == 0)
		return (0);
	*start = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if ((k == 0) && (s[i] != c))
		{
			*start = i;
			k = 1;
		}
		if ((s[i] == c) && (i != 0) && (s[i - 1] != c))
			num_of_strings++;
		i++;
	}
	if (s[i - 1] != c)
		num_of_strings++;
	return (num_of_strings);
}

int	static	len_s(char const *s, char c, int start)
{
	int	i;
	int	len_of_string;

	i = start;
	len_of_string = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		len_of_string++;
		i++;
	}
	return (len_of_string);
}

int	static	proceed_string(char *arr_str, char const *s, \
int start, char c)
{
	int	j;
	int	len_of_str;

	j = 0;
	len_of_str = len_s(s, c, start);
	while (j < len_of_str)
	{
		arr_str[j] = s[start + j];
		j++;
	}
	arr_str[j] = '\0';
	while (s[start + j] == c)
	{
		j++;
	}
	start += j;
	return (start);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_str;
	int		str_quan;
	int		start;
	int		i;

	if (s == NULL)
		return (NULL);
	str_quan = num_of_strings(s, c, &start);
	i = 0;
	arr_str = (char **)malloc((str_quan + 1) * sizeof(char *));
	if (arr_str == NULL)
		return (NULL);
	while (i < str_quan)
	{
		arr_str[i] = (char *)malloc((len_s(s, c, start) + 1) * sizeof(char));
		if (arr_str[i] == NULL)
		{
			ft_clear(&arr_str, i);
			return (NULL);
		}
		start = proceed_string(arr_str[i], s, start, c);
		i++;
	}
	arr_str[i] = NULL;
	return (arr_str);
}
