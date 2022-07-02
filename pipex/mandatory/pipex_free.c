/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 09:36:57 by bogdantiyan       #+#    #+#             */
/*   Updated: 2022/07/02 12:27:38 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free_commands(t_commands *commands)
{
	t_commands	*tmp;
	t_commands	*current;

	tmp = commands;
	while (tmp != NULL)
	{
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
	return (0);
}

int	ft_free_files(t_file *files)
{
	t_file	*tmp;
	t_file	*current;

	tmp = files;
	while (tmp != NULL)
	{
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
	return (0);
}

int	ft_free_processes(t_process_config *process)
{
	t_process_config	*tmp;
	t_process_config	*current;

	tmp = process;
	while (tmp != NULL)
	{
		ft_free_commands(tmp->command);
		ft_free_files(tmp->read_files);
		ft_free_files(tmp->out_files);
		ft_free(tmp->here_doc_pipes);
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
	return (0);
}

void	ft_print_list(t_process_config *list)
{
	t_process_config	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->command->command);
		if (tmp->out_files != NULL)
			printf("%s\n", tmp->out_files->file);
		if (tmp->read_files != NULL)
			printf("%s\n", tmp->read_files->file);
		if (tmp->heredoc != NULL)
			printf("%s\n", tmp->heredoc);
		printf("%d\n", tmp->im_last_flag);
		tmp = tmp->next;
	}
}
