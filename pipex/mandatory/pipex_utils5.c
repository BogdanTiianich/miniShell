/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/22 15:53:51 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_list(t_process_config *list)
{
	t_process_config	*tmp;
	int					count;

	tmp = list;
	count = 0;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->command->command);
		if (tmp->out_files != NULL)
			printf("%s\n", tmp->out_files->file);
		if (tmp->read_files != NULL)
			printf("%s\n", tmp->read_files->file);
		if (tmp->heredoc != NULL)
			printf("%s\n", tmp->heredoc);
		printf("%d\n", tmp->im_last_flag);
		tmp = tmp->next;
	}
}

int	ft_waiter(t_process_config *process_config)
{
	t_process_config	*tmp;
	int					count;

	count = 0;
	tmp = process_config;
	while (tmp != NULL)
	{
		if (waitpid(tmp->id, NULL, 0) == -1)
			return (1);
		printf("WAITING for %d\n", tmp->id);
		tmp = tmp->next;
	}
}

t_process_config	*ft_multi_exec(t_process_config *process_config, \
char	**commands, t_info *info, char **paths)
{
	t_process_config	*tmp;
	int					fd[2];

	tmp = process_config;
	while (tmp != NULL)
	{
		commands = ft_get_array(tmp->command);
		commands[0] = ft_check_access_new(commands[0], paths);
		ft_heredoc_handler(tmp);
		tmp = ft_pipes_layer(tmp, fd);
		tmp->id = fork();
		if (tmp->id == 0)
		{
			ft_handle_read_stuff(tmp);
			ft_handle_write_stuff(tmp);
			ft_close_pipes(process_config);
			if (ft_check_if_builtins(tmp, info) == 1)
				exit(1);
			execve(commands[0], \
			commands, info->envp);
			exit(1);
			ft_errors(1);
		}
		tmp = tmp->next;
	}
	return (process_config);
}

int	ft_pipex(char **arr_of_comands, t_info *info)
{
	t_vars				vars;
	t_process_config	*process_config;
	char				**paths;
	char				**commands;
	char				*cmd;

	process_config = ft_parce_commands(arr_of_comands, process_config);
	if (process_config == NULL)
		return (0);
	if (process_config->im_last_flag == 1)
	{
		if (ft_check_if_builtins(process_config, info) == 1)
			return (1);
	}
	paths = ft_get_path_new(info->envp);
	process_config = ft_multi_exec(process_config, \
commands, info, paths);
	ft_close_pipes(process_config);
	ft_waiter(process_config);
	printf("FINISH\n");
}
