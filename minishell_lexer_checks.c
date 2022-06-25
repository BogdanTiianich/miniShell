/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_checks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:40:07 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/17 14:40:08 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes_next(t_token *tmp)
{
	while (tmp != NULL)
	{
		skip_field(&tmp, EXP_FIELD);
		skip_field(&tmp, FIELD);
		if (tmp->token == 8)
		{
			if (tmp->next == NULL)
				return (0);
			else if (tmp->next->token == 8)
				return (0);
			else if (tmp->next->token == 0 && tmp->next->next == NULL)
				return (0);
			else if (tmp->next->next != NULL && \
					tmp->next->next->token == 8 && tmp->next->token == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_pipes(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		if (tmp->token == 8)
			return (0);
		else if (tmp->token == 0 && tmp->next != NULL && tmp->next->token == 8)
			return (0);
	}
	return (check_pipes_next(tmp));
}

int	check_redirects(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		skip_field(&tmp, EXP_FIELD);
		skip_field(&tmp, FIELD);
		if (tmp->token >= 4 && tmp->token <= 7)
		{
			if (tmp->next == NULL)
				return (0);
			else if (tmp->next->token >= 4 && tmp->next->token <= 7)
				return (0);
			else if (tmp->next->token == 0 && tmp->next->next == NULL)
				return (0);
			else if (tmp->next->next != NULL && tmp->next->token == 0 && \
					tmp->next->next->token >= 4 && tmp->next->next->token <= 7)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_new_lines(t_token **token, char *p)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *token;
	while (tmp != NULL)
	{
		if (!sub_check(tmp->token, p, &i))
			return (0);
		skip_field(&tmp, FIELD);
		skip_field(&tmp, EXP_FIELD);
		tmp = tmp->next;
	}
	return (1);
}

int	all_check(t_info *info, char *p)
{
	int	x;

	x = 0;
	if (!check_fields(&info->token))
		x = -1;
	else if (!check_pipes(&info->token))
		x = -2;
	else if (!check_redirects(&info->token) || \
		!check_new_lines(&info->token, p))
		x = -3;
	if (x != 0)
		all_free(info, x, NULL);
	return (x);
}
