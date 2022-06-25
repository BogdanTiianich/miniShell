/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/03 19:26:58 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_process	**process_init(t_process **processes, t_vars vars, t_pipes *pipes)
{
	int		iter;

	iter = vars.start;
	vars.num_of_processes = vars.num_of_processes + vars.start - 1;
	while (iter <= vars.num_of_processes)
	{
		vars.s = ft_split(vars.argv[iter], '\'');
		if (vars.s == NULL)
			ft_errors(pipes, processes);
		processes = process_malloc(processes, &vars, pipes, iter);
		ft_define_command(iter, &vars, pipes, processes);
		ft_check_access_big(iter, vars, pipes, processes);
		iter++;
	}
	return (processes);
}

t_pipes	*ft_start_pipes(int num_of_processes, t_vars vars, t_pipes *pipes)
{
	vars.i = 0;
	while (vars.i < num_of_processes - 1)
	{
		(*pipes).fds[vars.i] = (int *)malloc(sizeof(int [2]));
		if ((*pipes).fds[vars.i] == NULL)
			ft_errors(pipes, NULL);
		(*pipes).current_pipe_num = vars.i;
		if (pipe((*pipes).fds[vars.i]) == -1)
			ft_errors(pipes, NULL);
		vars.i++;
	}
	return (pipes);
}

t_pipes	*ft_init_pipes(int num_of_processes, t_pipes *pipes, t_vars vars)
{
	if (num_of_processes == 1)
		ft_errors(pipes, NULL);
	pipes = (t_pipes *)malloc(sizeof(t_pipes));
	if (pipes == NULL)
		ft_errors(pipes, NULL);
	(*pipes).fds = (int **)malloc(sizeof(int *) * num_of_processes);
	if ((*pipes).fds == NULL)
		ft_errors(pipes, NULL);
	(*pipes).fds[num_of_processes - 1] = NULL;
	(*pipes).last_pipe_num = num_of_processes - 1;
	vars.i = 0;
	while (vars.i < num_of_processes - 1)
	{
		(*pipes).fds[vars.i] = NULL;
		vars.i++;
	}
	pipes = ft_start_pipes(num_of_processes, vars, pipes);
	return (pipes);
}

void	ft_new_process_only(t_pipes *pipes, t_files files, \
t_process **processes, t_vars vars)
{
	if (duplicate_fd(vars.current_process, \
	vars.num_of_processes - 1, pipes, files) == 1)
		ft_errors(pipes, processes);
	ft_close_unnecessary_fds(pipes, processes);
	execve((*processes[vars.current_process]).command[0], \
	(*processes[vars.current_process]).command, vars.envp);
	ft_errors(pipes, processes);
}

int	ft_execute(t_pipes *pipes, t_files files, \
t_process **processes, t_vars vars)
{
	int	id;

	vars.current_process = 0;
	if (files.limiter != NULL)
	{
		if (ft_read_here_doc(files.limiter, pipes) != 0)
			ft_errors(pipes, processes);
	}
	while (vars.current_process < vars.num_of_processes)
	{
		id = fork();
		if (id == -1)
			ft_errors(pipes, processes);
		if (id == 0)
			ft_new_process_only(pipes, files, processes, vars);
		else
			(*processes[vars.current_process]).id = id;
		vars.current_process++;
	}
	ft_close_unnecessary_fds(pipes, processes);
	return (0);
}
