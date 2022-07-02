/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirects_and_pipes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 12:22:13 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_handle_read_stuff_part(t_process_config *process, t_file	*file)
{
	int		fd;

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
		{
			ft_errors(562, file->file);
			return (1);
		}
		if (dup2(fd, 0) == -1)
			ft_errors(1, "\0");
	}
	return (0);
}

int	ft_handle_read_stuff(t_process_config *process)
{
	t_file	*file;

	if (process->from_prev_pipe != -1)
		dup2(process->from_prev_pipe, 0);
	file = process->read_files;
	while (file != NULL)
	{
		if (ft_handle_read_stuff_part(process, file))
			return (1);
		file = file->next;
	}
	return (0);
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
			{
				ft_errors(339, file->file);
				exit(339);
			}
			if (dup2(fd, 1) == -1)
				ft_errors(1, "\0");
		}
		file = file->next;
	}
}

void	ft_pipes_creator(t_process_config *process)
{
	if (process->heredoc != NULL)
	{
		process->here_doc_pipes = (int *)malloc(sizeof(int) * 2);
		if (pipe(process->here_doc_pipes) != 0)
			ft_errors(1, "\0");
	}
}
