/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/21 20:11:59 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_process_config	*ft_pipes_layer(t_process_config *process, int fd[2])
{
	if (process->im_last_flag != 1)
	{
		if (pipe(fd) == -1)
			ft_errors(1);
		process->to_next_pipe = fd[1];
		process->next->from_prev_pipe = fd[0];
	}
	return (process);
}

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

void	ft_handle_read_stuff(t_process_config *process)
{
	t_file	*file;
	int		fd;

	if (process->from_prev_pipe != -1)
		dup2(process->from_prev_pipe, 0);
	file = process->read_files;
	while (file != NULL)
	{
		if (file->type_flag == 0)
		{
			ft_putstr_fd("DUPED_HEREDOC\n", 2);
			if (dup2(process->here_doc_pipes[0], 0) == -1)
				ft_errors(5);
			close(process->here_doc_pipes[0]);
			close(process->here_doc_pipes[1]);
		}
		if (file->type_flag == 1)
		{
			ft_putstr_fd("DUPED_READFILE\n", 2);
			fd = open(file->file, O_RDONLY);
			printf("FILE DESCRIPTOR READ %d   %s\n", fd, file->file);
			if (fd == -1)
				ft_errors(1);
			if (dup2(fd, 0) == -1)
				ft_errors(5);
			// close(fd);
		}	
		file = file->next;
	}
}

void	ft_handle_write_stuff(t_process_config *process)
{
	t_file	*file;
	int		fd;

	if (process->to_next_pipe != -1)
		dup2(process->to_next_pipe, 1);
	file = process->out_files;
	fd = -1;
	while (file != NULL)
	{
		if (file->type_flag == 2)
		{
			fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			// if (fd == -1)
			// 	ft_errors(1);
			// if (dup2(fd, 1) == -1)
			// 	ft_errors(5);
		}
		if (file->type_flag == 3)
			fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file->type_flag == 2 || file->type_flag == 3)
		{
			if (fd == -1)
				ft_errors(1);
			if (dup2(fd, 1) == -1)
				ft_errors(1);
		}
		file = file->next;
	}
}

void	ft_pipes_creator(t_process_config *process)
{
	t_process_config	*tmp;

	if (process->heredoc != NULL)
	{
		process->here_doc_pipes = (int *)malloc(sizeof(int) * 2);
		if (pipe(process->here_doc_pipes) != 0)
			ft_errors(1);
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

int	ft_heredoc_handler(t_process_config *process)
{
	int		id;
	char	*str;

	if (process->heredoc != NULL)
	{
		process->here_doc_pipes = (int *)malloc(sizeof(int) * 2);
		ft_check_malloc(process->here_doc_pipes);
		if (pipe(process->here_doc_pipes) == -1)
			ft_errors(1);
		id = fork();
		if (id == 0)
		{
			ft_putstr_fd("HEREDOC_IS_LISTENING\n", 2);
			printf("%s\n", ft_get_array(process->command)[0]);
			close(process->here_doc_pipes[0]);
			while (1)
			{
				str = get_next_line(0);
				if (str == NULL)
				{
					ft_putstr_fd("SMTH_WENT_WRONG IN HEREDOC\n", 2);
					close(process->here_doc_pipes[1]);
					exit(1);
				}
				if (ft_strncmp(str, process->heredoc, \
				ft_strlen(process->heredoc)) == 0 \
				&& ft_strlen(process->heredoc) == ft_strlen(str) - 1)
				{
					free(str);
					ft_putstr_fd("FOUND STOP-WORD\n", 2);
					close(process->here_doc_pipes[1]);
					exit(1);
				}
				write(process->here_doc_pipes[1], str, ft_strlen(str));
				free(str);
			}	
		}
		waitpid(id, NULL, 0);
	}
}

void	ft_close_pipes(t_process_config *process)
{
	t_process_config	*tmp;

	tmp = process;
	while (tmp != NULL)
	{
		close(tmp->from_prev_pipe);
		close(tmp->to_next_pipe);
		if (tmp->here_doc_pipes != NULL)
		{
			close(tmp->here_doc_pipes[0]);
			close(tmp->here_doc_pipes[1]);
		}
		tmp = tmp->next;
	}
}

int	ft_pipex(char **arr_of_comands, t_info *info)
{
	t_vars				vars;
	t_process_config	*process_config;
	t_process_config	*tmp;
	int					fd[2];
	char 				**paths;
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
			ft_errors(1);
		}
		tmp = tmp->next;
	}
	ft_close_pipes(process_config);
	ft_waiter(process_config);
	printf("FINISH\n");
}
