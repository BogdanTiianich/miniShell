/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser_for_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:00:35 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 10:53:11 by bogdantiyan      ###   ########.fr       */
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

void	ft_parce_command_part(t_vars *vars, t_process_config **process_config)
{
	*process_config = NULL;
	vars->count = 0;
	vars->last_flag = 0;
	vars->right_side = 0;
	vars->left_side = 0;
}

t_process_config	*ft_parce_commands(char **arr_of_comands, \
t_process_config	*process_config)
{
	int					j;
	t_vars				vars;
	t_process_config	*tmp;

	ft_parce_command_part(&vars, &process_config);
	while (2)
	{
		while (arr_of_comands[vars.right_side] != NULL && \
		ft_strncmp(arr_of_comands[vars.right_side], "|\0", 1) != 0)
			vars.right_side++;
		if (arr_of_comands[vars.right_side] == NULL)
			vars.last_flag = 1;
		tmp = ft_create_proc_elem(vars.count);
		vars.count++;
		j = vars.left_side;
		tmp = ft_parce_one_command(tmp, j, arr_of_comands, vars.right_side);
		tmp->im_last_flag = vars.last_flag;
		process_config = (t_process_config *)add_to_end(process_config, tmp, 1);
		if (vars.last_flag == 1)
			break ;
		vars.left_side = vars.right_side + 1;
		vars.right_side += 1;
	}
	return (process_config);
}
