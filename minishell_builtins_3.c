/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:14:57 by bogdantiyan       #+#    #+#             */
/*   Updated: 2022/07/02 12:15:30 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_builtins(t_process_config *process, t_info *info)
{
	char	**command;
	int		res;

	res = ft_chech_words(process, info);
	if (res == 1)
	{
		ft_check_builtins_part1(process, info);
		command = ft_get_array_com(process->command);
		command++;
		if (ft_strncmp(process->command->command, EXPORT, \
		ft_strlen(EXPORT)) == 0)
			info->envp_list = ft_export(info->envp_list, \
			command);
		if (ft_strncmp(process->command->command, UNSET, ft_strlen(UNSET)) == 0)
			info = ft_unset(info, command);
		if (ft_strncmp(process->command->command, CD, ft_strlen(CD)) == 0)
			info->envp_list = ft_cd(ft_get_array_com(process->command)[1], \
			&(info->envp_list));
		info->status = 0;
		return (1);
	}
	if (res == 2)
		return (2);
	return (0);
}

t_lists	*ft_unlink_elem_from_list(t_lists *list, char *unset, int free_flag)
{
	t_lists	*tmp;
	t_lists	*prev_elem_env;
	int		len_unset;

	tmp = list;
	prev_elem_env = NULL;
	len_unset = ft_strlen(unset);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, unset, len_unset) == 0)
		{
			prev_elem_env->next = tmp->next;
			if (free_flag)
			{
				ft_free(tmp->key);
				ft_free(tmp->value);
				free(tmp);
			}
			break ;
		}
		prev_elem_env = tmp;
		tmp = tmp->next;
	}
	return (list);
}

t_info	*ft_unset(t_info *info, char **unset)
{
	int		i;
	t_lists	*list;

	list = info->envp_list;
	i = 0;
	while (unset[i] != NULL)
	{
		if (ft_exp_uns_name(unset[i]) == 1)
		{
			ft_errors(523, unset[i]);
			info->status = 1;
		}	
		else
			list = ft_unlink_elem_from_list(list, unset[i], 1);
		i++;
	}
	free(info->envp);
	info->envp = ft_get_array_list(list);
	info->envp_list = list;
	return (info);
}

int	ft_check_n_arg_echo(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0' || i == 1)
		return (0);
	return (1);
}

int	ft_check_exit_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_errors(335, "too many arguments\0");
		return (1);
	}
	i = 0;
	while (arg[1][i] != '\0')
	{
		if (!ft_isdigit(arg[1][i]))
		{
			ft_errors(336, arg[1]);
			exit(1);
		}
		i++;
	}
	return (0);
}
