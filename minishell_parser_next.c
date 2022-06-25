/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:40:34 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/24 15:12:22 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*re_command(char *str, char *env, int i)
{
	int		count;
	char	*new_str;

	count = i++;
	while (!is_not_word(str[i]))
		++i;
	if (env != NULL)
		new_str = (char *)malloc(sizeof (char) * \
			(ft_strlen(str) - 1 - i + count + ft_strlen(env)));
	else
		new_str = (char *)malloc(sizeof (char) * (ft_strlen(str) - i + count));
	if (!new_str)
		return (NULL);
	new_str = ft_copy(new_str, str, env, count);
	free(str);
	return (new_str);
}

void	copy_question(char *dst, char *src, int status)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (src[i] != '$')
		dst[j++] = src[i++];
	i += 2;
	if (status == 0)
		dst[j++] = '0';
	else
		ft_itoan(dst, status, &j);
	while (src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
}

char	*question(char *str, int status)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * \
		(ft_strlen(str) - 2 + count_status(status)));
	if (!new_str)
		return (NULL);
	copy_question(new_str, str, status);
	free(str);
	return (new_str);
}

t_command	*skip_or_open(t_command *cmd, int *i, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->str[*i] == '$')
	{
		tmp = check_env_var(info->envp_list, &(cmd->str[*i + 1]));
		if (cmd->str[*i + 1] == '?')
			cmd->str = question(cmd->str, info->status);
		else
			cmd->str = re_command(cmd->str, tmp, *i);
		--*i;
	}
	return (cmd);
}

int	opening_dollar(t_command *cmd, int *i, t_info *info)
{
	while (cmd->str[*i])
	{
		if (cmd->str[*i] == '\"')
		{
			while (cmd->str[++*i] && cmd->str[*i] != '\"')
				cmd = skip_or_open(cmd, i, info);
			++*i;
		}
		else if (is_token(cmd->str[*i]) == WORD)
		{
			while (is_token(cmd->str[*i]) == WORD)
			{
				cmd = skip_or_open(cmd, i, info);
				++*i;
			}
		}
		else if (cmd->str[*i] == '\'')
		{
			skip_words(FIELD, cmd->str, i);
		}
	}
	return (0);
}
