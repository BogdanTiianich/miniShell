/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/03 19:26:51 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_check_access(char *command_name, char **path)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	tmp = NULL;
	s = NULL;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		if (tmp == NULL)
			return (NULL);
		s = ft_strjoin(tmp, command_name);
		if (s == NULL)
			return (NULL);
		ft_free(tmp);
		tmp = NULL;
		if (access(s, 1) == 0)
			return (s);
		else
			free(s);
		i++;
	}
	return (NULL);
}

int	ft_strcmp_hand(char *s1, char*s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}

int	num_of_strings(char const *s, char c, int start)
{
	int	i;
	int	num_of_strings;
	int	k;

	i = 0;
	num_of_strings = 0;
	if (ft_strlen(s) == 0)
		return (0);
	start = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if ((k == 0) && (s[i] != c))
		{
			start = i;
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

char	**ft_find_word_path(char **envp, int *success_flag)
{
	char	**s;
	int		i;

	i = 0;
	success_flag = 0;
	while (envp[i] != NULL)
	{
		s = ft_split(envp[i], '=');
		if (s != NULL)
		{		
			if (ft_strcmp_hand(s[0], "PATH") == 0)
			{
				return (s);
			}
			ft_split_free(s);
		}
		else
			return (NULL);
		i++;
	}
	return (NULL);
}
