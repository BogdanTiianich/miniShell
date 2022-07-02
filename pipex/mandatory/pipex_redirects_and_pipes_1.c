/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirects_and_pipes_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 12:09:34 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
