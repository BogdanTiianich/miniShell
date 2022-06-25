/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 17:20:15 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_heredoc_runner(t_process_config *process)
{
	char	*str;

	close(process->here_doc_pipes[0]);
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
		{
			close(process->here_doc_pipes[1]);
			exit(1);
		}
		if (ft_strncmp(str, process->heredoc, \
		ft_strlen(process->heredoc)) == 0 \
		&& ft_strlen(process->heredoc) == ft_strlen(str) - 1)
		{
			free(str);
			close(process->here_doc_pipes[1]);
			exit(1);
		}
		write(process->here_doc_pipes[1], str, ft_strlen(str));
		free(str);
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
			ft_errors(1, "\0");
		id = fork();
		if (id == 0)
			ft_heredoc_runner(process);
		waitpid(id, NULL, 0);
	}
}
