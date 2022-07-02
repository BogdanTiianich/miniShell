/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 12:26:38 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_info	*ft_waiter(t_process_config *process_config, t_info *info)
{
	t_process_config	*tmp;
	int					exitstat;

	tmp = process_config;
	while (tmp != NULL)
	{
		if (waitpid(tmp->id, &exitstat, 0) == -1)
			ft_errors(1, "Waitpid broke\0");
		if (WIFEXITED(exitstat))
		{
			info->status = WEXITSTATUS(exitstat);
		}
		tmp = tmp->next;
	}
	return (info);
}

void	ft_multi_exec_fork_part(t_process_config *process_config, \
char	**commands, char	*cmd, t_process_config	*tmp)
{
	if (tmp->id == 0)
	{
		if (ft_handle_read_stuff(tmp))
			exit (1);
		ft_handle_write_stuff(tmp);
		ft_close_pipes(process_config);
		if (cmd == NULL)
		{
			ft_errors(300, commands[0]);
			exit (1);
		}
	}
}

t_process_config	*ft_multi_exec(t_process_config *process_config, \
char	**commands, t_info *info, char **paths)
{
	t_process_config	*tmp;
	int					fd[2];
	char				*cmd;

	tmp = process_config;
	while (tmp != NULL)
	{
		commands = ft_get_array_com(tmp->command);
		cmd = ft_check_access_new(commands[0], paths);
		ft_heredoc_handler(tmp);
		tmp = ft_pipes_layer(tmp, fd);
		tmp->id = fork();
		if (tmp->id == 0)
		{
			ft_multi_exec_fork_part(process_config, commands, cmd, tmp);
			if (ft_check_if_builtins(tmp, info) == 1)
				exit(1);
			execve(cmd, commands, info->envp);
			ft_errors(1, "\0");
			exit(1);
		}
		free(cmd);
		tmp = tmp->next;
	}
	return (process_config);
}

int	ft_lonely_biultin(t_process_config	*process_config, \
t_info *info)
{
	t_vars	vars;

	if (process_config->im_last_flag == 1)
	{
		vars.saved_dup_read = dup(0);
		vars.saved_dup_write = dup(1);
		if (ft_check_if_builtins(process_config, info) > 0)
		{
			dup2(vars.saved_dup_read, 0);
			dup2(vars.saved_dup_write, 1);
			ft_free_processes(process_config);
			return (1);
		}
	}
	return (0);
}

int	ft_pipex(char **arr_of_comands, t_info *info)
{
	t_process_config	*process_config;
	char				**paths;
	char				**commands;

	commands = NULL;
	process_config = NULL;
	process_config = ft_parce_commands(arr_of_comands, process_config);
	if (process_config == NULL)
		return (0);
	if (ft_lonely_biultin(process_config, info))
		return (1);
	paths = ft_get_path_new(info->envp);
	process_config = ft_multi_exec(process_config, \
commands, info, paths);
	ft_close_pipes(process_config);
	info = ft_waiter(process_config, info);
	ft_split_free(paths);
	ft_free_processes(process_config);
	return (0);
}
