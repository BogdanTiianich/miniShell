/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsers_searchers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:00:35 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/15 13:48:04 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path_new(char **env)
{
	int		i;
	char	**ans;
	char	**paths;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0 && env[i] != NULL)
		i++;
	if (env[i] == NULL)
		return (NULL);
	ans = ft_split(env[i], '=');
	if (ans == NULL)
		return (NULL);
	paths = ft_split(ans[1], ':');
	ft_split_free(ans);
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	**ft_get_array(t_commands *list)
{
	t_commands	*tmp;
	int			count;
	char		**arr;

	tmp = list;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	ft_check_malloc(arr);
	tmp = list;
	count = 0;
	while (tmp)
	{
		arr[count] = tmp->command;
		tmp = tmp->next;
		count++;
	}
	arr[count] = NULL;
	return (arr);
}

char	*ft_check_access_new(char *cmd, char **paths)
{
	char	*path;
	int		i;
	char	*s;
	char	*tmp;

	if (access(cmd, 1) == -1)
	{
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			ft_check_malloc(tmp);
			s = ft_strjoin(tmp, cmd);
			ft_check_malloc(s);
			free(tmp);
			if (access(s, 1) != -1)
				return (s);
			free(s);
			i++;
		}
	}
	return ("No command\0");//???
}

t_process_config	*ft_parce_commands(char **arr_of_comands, \
t_process_config	*process_config)
{
	int					j;
	int					last_flag;
	int					left_side;
	int					right_side;
	t_process_config	*tmp;
	t_file				*tmp_file;
	int					count;

	process_config = NULL;
	count = 0;
	last_flag = 0;
	right_side = 0;
	left_side = 0;
	while (2)
	{
		while (arr_of_comands[right_side] != NULL && \
		ft_strncmp(arr_of_comands[right_side], "|\0", 1) != 0)
			right_side++;		
		if (arr_of_comands[right_side] == NULL)
			last_flag = 1;
		tmp = ft_create_proc_elem(count);
		count++;
		j = left_side;
		while (j < right_side)
		{
			if (ft_strncmp(arr_of_comands[j], "<<", 2) == 0)
			{
				j += 2;
				tmp->heredoc = arr_of_comands[j - 1];
				tmp->read_files = (t_file *)add_to_end(tmp->read_files, \
				ft_create_file_elem(arr_of_comands[j - 1], 0), 2);
				continue ;
			}
			if (ft_strncmp(arr_of_comands[j], "<", 1) == 0)
			{
				j += 2;
				tmp->read_files = (t_file *)add_to_end(tmp->read_files, \
				ft_create_file_elem(arr_of_comands[j - 1], 1), 2);
				continue ;
			}
			if (ft_strncmp(arr_of_comands[j], ">>", 2) == 0)
			{
				j += 2;
				tmp->out_files = (t_file *)add_to_end(tmp->out_files, \
				ft_create_file_elem(arr_of_comands[j - 1], 3), 2);
				continue ;
			}
			if (ft_strncmp(arr_of_comands[j], ">", 1) == 0)
			{
				j += 2;
				tmp->out_files = (t_file *)add_to_end(tmp->out_files, \
				ft_create_file_elem(arr_of_comands[j - 1], 2), 2);
				continue ;
			}
			tmp->command = (t_commands *)add_to_end(tmp->command, \
			ft_create_command_elem(arr_of_comands[j]), 3);
			j++;
		}
		tmp->im_last_flag = last_flag;
		process_config = (t_process_config *)add_to_end(process_config, tmp, 1);
		if (last_flag == 1)
			break ;
		left_side = right_side + 1;
		right_side += 1;
	}
	return (process_config);
}
