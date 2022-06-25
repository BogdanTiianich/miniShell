/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/03 19:26:49 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	duplicate_fd(int current_process_num, int num_of_last_process, \
t_pipes *pipes, t_files files)
{
	if (current_process_num == 0)
	{
		if (ft_handle_dup_first_proc(files, pipes) == 1)
			return (1);
	}
	else
	{
		if (current_process_num == num_of_last_process)
		{
			if (ft_handle_dup_last_proc(files, pipes, \
			current_process_num) == -1)
				return (1);
		}
		else
		{
			if (dup2((*pipes).fds[current_process_num - 1][0], 0) == -1)
				return (1);
			if (dup2((*pipes).fds[current_process_num][1], 1) == -1)
				return (1);
		}
	}
	return (0);
}

void	ft_not_in_quotes_part(int iter, t_vars *vars, \
t_pipes *pipes, t_process **processes)
{
	char	**tmp;

	tmp = ft_split((*vars).s[(*vars).i], ' ');
	if (tmp == NULL)
	{
		ft_split_free((*vars).s);
		ft_errors(pipes, processes);
	}
	(*vars).j = 0;
	while (tmp[(*vars).j] != NULL)
	{
		(*processes[iter - (*vars).start]).command[(*vars).counter] = \
		tmp[(*vars).j];
		(*vars).j++;
		(*vars).counter++;
	}
	free(tmp);
}

void	ft_define_command(int iter, t_vars *vars, \
t_pipes *pipes, t_process **processes)
{
	(*vars).i = 0;
	(*vars).counter = 0;
	while ((*vars).s[(*vars).i] != NULL)
	{
		if ((*vars).i % 2)
		{
			(*processes[iter - (*vars).start]).command[(*vars).counter] \
			= (*vars).s[(*vars).i];
			(*vars).counter++;
		}
		else
		{
			ft_not_in_quotes_part(iter, vars, pipes, processes);
		}
		(*vars).i++;
	}
	ft_split_free((*vars).s);
	(*processes[iter - (*vars).start]).command[(*vars).counter] = NULL;
}

void	ft_check_access_big(int iter, t_vars vars, \
t_pipes *pipes, t_process **processes)
{
	char	*tmp2;

	if (access((*processes[iter - vars.start]).command[0], 1) == -1)
	{
		vars.s = ft_get_path(vars.envp);
		if (vars.s == NULL)
			ft_errors(pipes, processes);
		tmp2 = ft_check_access((*processes[iter - \
		vars.start]).command[0], vars.s);
		ft_split_free(vars.s);
		ft_free((*processes[iter - vars.start]).command[0]);
		if (tmp2 == NULL)
			ft_errors(pipes, processes);
		(*processes[iter - vars.start]).command[0] = tmp2;
	}
	(*processes[iter - vars.start]).current_process_num = iter - vars.start;
	(*processes[iter - vars.start]).last_process_num = \
	vars.num_of_processes - 2;
}

t_process	**process_malloc(t_process **processes, \
t_vars *vars, t_pipes *pipes, int iter)
{
	processes[iter - (*vars).start] = (t_process *)malloc(sizeof(t_process));
	if (processes[iter - (*vars).start] == NULL)
	{
		ft_split_free((*vars).s);
		ft_errors(pipes, processes);
	}
	(*processes[iter - (*vars).start]).command = (char **)malloc((\
	num_of_strings((*vars).argv[iter], ' ', 0) + 1) * sizeof(char *));
	if ((*processes[iter - (*vars).start]).command == NULL)
	{
		ft_split_free((*vars).s);
		ft_errors(pipes, processes);
	}
	return (processes);
}
