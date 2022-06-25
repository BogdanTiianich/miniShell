/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirects_and_pipes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 17:20:03 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			if (dup2(process->here_doc_pipes[0], 0) == -1)
				ft_errors(1, "\0");
			close(process->here_doc_pipes[0]);
			close(process->here_doc_pipes[1]);
		}
		if (file->type_flag == 1)
		{
			fd = open(file->file, O_RDONLY);
			if (fd == -1)
				ft_errors(1, "\0");
			if (dup2(fd, 0) == -1)
				ft_errors(1, "\0");
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
			fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file->type_flag == 3)
			fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file->type_flag == 2 || file->type_flag == 3)
		{
			if (fd == -1)
				ft_errors(1, "\0");
			if (dup2(fd, 1) == -1)
				ft_errors(1, "\0");
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
			ft_errors(1, "\0");
	}
}

t_process_config	*ft_pipes_layer(t_process_config *process, int fd[2])
{
	if (process->im_last_flag != 1)
	{
		if (pipe(fd) == -1)
			ft_errors(1, "\0");
		process->to_next_pipe = fd[1];
		process->next->from_prev_pipe = fd[0];
	}
	return (process);
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
