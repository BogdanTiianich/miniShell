/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:40:59 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/17 15:18:40 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_check(int token, char *p, int *i)
{
	if (token == WORD)
	{
		while (is_token(p[*i]) == WORD)
		{
			if (p[*i] == 92 || p[*i] == ';')
				return (0);
			++*i;
		}
	}
	else
	{
		if (token == 2 || token == 3)
		{
			++*i;
			while (is_token(p[*i]) != token && p[*i])
				++*i;
			++*i;
		}
		else
		{
			while (is_token(p[*i]) == token && p[*i])
				++*i;
		}
	}
	return (1);
}

char	*check_env_var(t_lists *envp_list, char *str)
{
	t_lists	*tmp;

	tmp = envp_list;
	while (tmp != NULL)
	{
		if (ft_strcmp_v2(tmp->key, str))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_copy(char *dst, char *src, char *env, int x)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (j != x)
		dst[i++] = src[j++];
	j++;
	while (!is_not_word(src[j]))
		++j;
	if (env != NULL)
	{
		while (env[k])
			dst[i++] = env[k++];
	}
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

void	ft_strcopy2(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != '\'' && src[i] != '\"')
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
}
