/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:40:25 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/17 14:40:27 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_field(t_token **token, int x)
{
	if ((*token)->token == x)
	{
		*token = (*token)->next;
		while ((*token)->token != x)
			*token = (*token)->next;
		return (1);
	}
	return (0);
}

int	check_fields(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		if (tmp->token == FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != FIELD)
				tmp = tmp->next;
		}
		else if (tmp->token == EXP_FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != EXP_FIELD)
			{
				tmp = tmp->next;
			}
		}
		if (tmp == NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	count_list(t_command *command)
{
	int	count;

	count = 0;
	while (command != NULL)
	{
		if (command->str[0])
			++count;
		command = command->next;
	}
	return (count);
}

int	count_fields(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			count += 2;
			skip_words(is_token(str[i]), str, &i);
			--i;
		}
		++i;
	}
	return (count);
}

char	**parser(t_command **command)
{
	char		**str;
	t_command	*tmp;
	int			i;

	tmp = *command;
	str = NULL;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (count_list(tmp) + 1));
	if (!str)
		return (NULL);
	while (i < count_list(*command))
	{
		if (tmp->str[0])
		{
			str[i] = (char *)malloc(sizeof(char) * \
				(ft_strlen(tmp->str) - count_fields(tmp->str)));
			if (!str[i])
				return (NULL);
			ft_strcopy2(str[i], tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}
