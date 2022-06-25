/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser_for_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:00:35 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/22 16:07:16 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_process_config	*ft_piece_of_code1(t_process_config \
*tmp, int *j, int file_type, char **arr_of_comands)
{
	*j += 2;
	if (file_type == 0)
		tmp->heredoc = arr_of_comands[*j - 1];
	if (file_type == 0 || file_type == 1)
		tmp->read_files = (t_file *)add_to_end(tmp->read_files, \
		ft_create_file_elem(arr_of_comands[*j - 1], file_type), 2);
	if (file_type == 2 || file_type == 3)
		tmp->out_files = (t_file *)add_to_end(tmp->out_files, \
		ft_create_file_elem(arr_of_comands[*j - 1], file_type), 2);
	return (tmp);
}

t_process_config	*ft_piece_of_code2(t_process_config \
*tmp, int *j, char **arr_of_comands)
{
	if (ft_strncmp(arr_of_comands[*j], "<<", 2) == 0)
	{
		tmp = ft_piece_of_code1(tmp, j, 0, arr_of_comands);
		return (tmp);
	}
	if (ft_strncmp(arr_of_comands[*j], "<", 1) == 0)
	{
		tmp = ft_piece_of_code1(tmp, j, 1, arr_of_comands);
		return (tmp);
	}
	if (ft_strncmp(arr_of_comands[*j], ">>", 2) == 0)
	{
		tmp = ft_piece_of_code1(tmp, j, 3, arr_of_comands);
		return (tmp);
	}
	if (ft_strncmp(arr_of_comands[*j], ">", 1) == 0)
	{
		tmp = ft_piece_of_code1(tmp, j, 2, arr_of_comands);
		return (tmp);
	}
	return (NULL);
}

t_process_config	*ft_parce_one_command(t_process_config \
*a_command, int j, char **arr_of_comands, int right_side)
{
	t_process_config	*tmp;

	while (j < right_side)
	{
		tmp = NULL;
		tmp = ft_piece_of_code2(a_command, &j, arr_of_comands);
		if (tmp != NULL)
		{
			a_command = tmp;
			continue ;
		}
		a_command->command = (t_commands *)add_to_end(a_command->command, \
		ft_create_command_elem(arr_of_comands[j]), 3);
		j++;
	}
	return (a_command);
}

t_process_config	*ft_parce_commands(char **arr_of_comands, \
t_process_config	*process_config)
{
	int					j;
	int					last_flag;
	int					left_side;
	int					right_side;
	t_vars				vars;
	t_process_config	*tmp;
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
		tmp = ft_parce_one_command(tmp, j, arr_of_comands, right_side);
		tmp->im_last_flag = last_flag;
		process_config = (t_process_config *)add_to_end(process_config, tmp, 1);
		if (last_flag == 1)
			break ;
		left_side = right_side + 1;
		right_side += 1;
	}
	return (process_config);
}

