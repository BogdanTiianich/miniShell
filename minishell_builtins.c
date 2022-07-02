/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:39:44 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 12:17:41 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_info *info)
{
	ft_print_lists(info->envp_list, NULL);
}

t_lists	*ft_create_list_elem(char *key, char *value)
{
	t_lists	*elem;

	if (!key || !value)
		return (NULL);
	elem = (t_lists *)malloc(sizeof(t_lists));
	ft_check_malloc(elem);
	elem->key = key;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

int	ft_chech_words(t_process_config *process, t_info *info)
{
	if (ft_strncmp(process->command->command, PWD, ft_strlen(PWD)) == 0 || \
	ft_strncmp(process->command->command, ENV, ft_strlen(ENV)) == 0 || \
	ft_strncmp(process->command->command, EXPORT, ft_strlen(EXPORT)) == 0 || \
	ft_strncmp(process->command->command, UNSET, ft_strlen(UNSET)) == 0 || \
	ft_strncmp(process->command->command, CD, ft_strlen(CD)) == 0 || \
	ft_strncmp(process->command->command, ECHO, ft_strlen(ECHO)) == 0 || \
	ft_strncmp(process->command->command, EXIT, ft_strlen(EXIT)) == 0)
	{
		ft_heredoc_handler(process);
		if (ft_handle_read_stuff(process))
		{
			info->status = 1;
			return (2);
		}	
		ft_handle_write_stuff(process);
		return (1);
	}
	return (0);
}

void	ft_check_builtins_part1(t_process_config *process, t_info *info)
{
	char	**command;

	if (ft_strncmp(process->command->command, PWD, ft_strlen(PWD)) == 0)
		ft_pwd(1);
	if (ft_strncmp(process->command->command, ENV, ft_strlen(ENV)) == 0)
		ft_env(info);
	if (ft_strncmp(process->command->command, ECHO, ft_strlen(ECHO)) == 0)
	{
		command = ft_get_array_com(process->command);
		command++;
		ft_echo(command);
	}
	if (ft_strncmp(process->command->command, EXIT, ft_strlen(EXIT)) == 0)
	{
		command = ft_get_array_com(process->command);
		ft_exit(command);
	}
}
