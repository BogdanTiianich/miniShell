/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/03 19:26:51 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_get_path(char **envp)
{
	char	**ss;
	int		success_flag;
	char	**s;

	ss = NULL;
	s = ft_find_word_path(envp, &success_flag);
	if (s == NULL)
		return (NULL);
	else
	{
		ss = ft_split(s[1], ':');
		ft_split_free(s);
		return (ss);
	}
	return (NULL);
}

int	ft_close_unnecessary_fds(t_pipes *pipes, t_process **processes)
{
	int	i;

	i = 0;
	while (i < (*pipes).last_pipe_num)
	{
		if (close((*pipes).fds[i][0]) == -1)
			ft_errors(pipes, processes);
		if (close((*pipes).fds[i][1]) == -1)
			ft_errors(pipes, processes);
		i++;
	}
	return (0);
}

int	ft_read_here_doc(char *limiter, t_pipes *pipes)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
		{
			return (1);
		}
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 \
		&& ft_strlen(limiter) == ft_strlen(str) - 1)
		{
			free(str);
			return (0);
		}
		write((*pipes).fds[(*pipes).last_pipe_num - 1][1], str, ft_strlen(str));
		free(str);
	}
	return (1);
}

int	ft_handle_dup_first_proc(t_files files, t_pipes *pipes)
{
	int	fd;

	if (files.limiter == NULL)
	{
		fd = open(files.input_file_name, O_RDONLY);
		if (fd == -1)
			return (1);
		if (dup2(fd, 0) == -1)
			return (1);
		if (close(fd) == -1)
			return (1);
	}
	else
		if (dup2((*pipes).fds[(*pipes).last_pipe_num - 1][0], 0) == -1)
			return (1);
	if (dup2((*pipes).fds[0][1], 1) == -1)
		return (1);
	return (0);
}

int	ft_handle_dup_last_proc(t_files files, \
t_pipes *pipes, int current_process_num)
{
	int	fd;

	if (dup2((*pipes).fds[current_process_num - 1][0], 0) == -1)
		return (1);
	fd = open(files.output_file_name, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (1);
	if (dup2(fd, 1) == -1)
		return (1);
	if (close(fd) == -1)
		return (1);
	return (0);
}
