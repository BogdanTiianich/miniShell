/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_with_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:39:43 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/17 15:18:14 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_free(t_info *info, int flag, t_command **command)
{
	if (info->token != NULL)
		free_token(&info->token);
	if (command != NULL && *command != NULL)
		ft_free_command(command);
	if (flag == 1)
	{
		ft_free_array(info->envp);
		ft_free_list(&info->envp_list);
	}
	if (flag < 1)
		print_error(info, flag);
}

void	*ft_free_list(t_lists **envp_list)
{
	t_lists	*tmp;

	tmp = *envp_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free((*envp_list)->key);
		free((*envp_list)->value);
		free(*envp_list);
		*envp_list = tmp;
	}
	free((*envp_list)->key);
	free((*envp_list)->value);
	free((*envp_list));
	*envp_list = NULL;
	return (NULL);
}

void	**ft_free_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
	envp = NULL;
	return (NULL);
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			free(*token);
			*token = NULL;
			*token = tmp;
		}
		free(*token);
		*token = NULL;
	}
}

void	ft_free_command(t_command **command)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free((*command)->str);
		free(*command);
		*command = tmp;
	}
	free((*command)->str);
	free(*command);
	*command = NULL;
}
