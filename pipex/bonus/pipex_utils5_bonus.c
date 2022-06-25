/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/09 17:12:55 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_waiter(int num_of_processes, t_process **processes)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		if (waitpid((*processes[i]).id, NULL, 0) == -1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_check_here_doc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0 \
	&& ft_strlen(argv[1]) == 8)
	{
		return (argv[2]);
	}
	return (NULL);
}

void	init_variables(t_vars *vars, t_files *files)
{
	(*files).limiter = ft_check_here_doc((*vars).argv);
	if ((*files).limiter == NULL)
	{
		(*files).input_file_name = (*vars).argv[1];
		(*vars).num_of_processes = (*vars).argc - 3;
		(*vars).start = 2;
		if ((*vars).argc < 5)
		{
			ft_putstr_fd("number of commands is not enough\n", 2);
			exit(1);
		}
	}
	else
	{
		(*vars).num_of_processes = (*vars).argc - 4;
		(*vars).start = 3;
		if ((*vars).argc < 6)
		{
			ft_putstr_fd("number of commands is not enough\n", 2);
			exit(1);
		}
	}
	(*files).output_file_name = (*vars).argv[(*vars).argc - 1];
}

t_process	**init_process_and_pipe(t_process **processes, t_vars vars, \
t_pipes **pipes, t_files files)
{
	processes = (t_process **)malloc(vars.num_of_processes * \
	sizeof(t_process *));
	if (processes == NULL)
		ft_errors((*pipes), processes);
	vars.i = 0;
	while (vars.i < vars.num_of_processes)
	{
		processes[vars.i] = NULL;
		vars.i++;
	}
	if (files.limiter != NULL)
		(*pipes) = ft_init_pipes(vars.num_of_processes + 1, (*pipes), vars);
	else
		(*pipes) = ft_init_pipes(vars.num_of_processes, (*pipes), vars);
	processes = process_init(processes, vars, (*pipes));
	return (processes);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_pipes		*pipes;
	t_process	**processes;
	t_vars		vars;
	t_files		files;

	processes = NULL;
	pipes = NULL;
	if (argc < 5)
	{
		ft_putstr_fd("number of commands is not enough\n", 2);
		exit(1);
	}
	vars.envp = envp;
	vars.argv = argv;
	vars.argc = argc;
	init_variables(&vars, &files);
	processes = init_process_and_pipe(processes, vars, &pipes, files);
	ft_execute(pipes, files, processes, vars);
	if (ft_waiter(vars.num_of_processes, processes) == 1)
		ft_errors(pipes, processes);
}
