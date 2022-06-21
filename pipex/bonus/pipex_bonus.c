/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/03 19:26:54 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(void *pointer)
{
	if (pointer != NULL)
	{
		free(pointer);
		pointer = NULL;
	}
}

int	ft_split_free(char **s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != NULL)
		{
			ft_free(s[i]);
			i++;
		}
		ft_free(s);
	}
	return (0);
}

void	ft_free_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	if (pipes != NULL)
	{
		while (i < (*pipes).last_pipe_num)
		{
			ft_free((*pipes).fds[i]);
			i++;
		}
		ft_free((*pipes).fds);
		ft_free(pipes);
	}
}

void	ft_free_processes(t_process **processes)
{
	int	i;
	int	num_of_processes;

	i = 0;
	num_of_processes = 3;
	if (processes != NULL)
	{	
		while (i < num_of_processes)
		{
			if (processes[i] != NULL)
			{
				ft_free(processes[i]);
			}
			i++;
		}
		ft_free(processes);
	}
}

void	ft_errors(t_pipes *pipes, t_process **processes)
{
	write(2, "got in error function\n", 22);
	ft_putstr_fd(strerror(errno), 2);
	ft_free_pipes(pipes);
	ft_free_processes(processes);
	exit(1);
}
