/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 10:59:56 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_split_print(char **s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != NULL)
		{
			ft_putstr_fd(s[i], 2);
			i++;
		}
	}
	return (0);
}

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

int	ft_errors(int code, char *str)
{
	char	*sada;

	ft_putnbr_fd(code, 2);
	sada = ft_create_str(str);
	if (code == 5454)
		printf("minishell: export: '%s' not a valid identifer\n", sada);
	if (code == 523)
		printf("minishell: unset: '%s' not a valid identifer\n", sada);
	if (code == 300)
		printf("minishell: '%s': command not found\n", sada);
	if (code == 335)
		printf("minishell: exit: %s\n", sada);
	if (code == 336)
		printf("minishell: exit: %s: numeric argument required\n", sada);
	if (code == 339)
		printf("minishell: %s: numeric argument required\n", sada);
	if (code == 562)
		printf("minishell: %s: No such file or directory\n", sada);
	free(sada);
	if (code < 300)
		ft_putstr_fd(strerror(errno), 2);
	return (0);
}

void	ft_check_malloc(void *data)
{
	if (data == NULL)
		ft_errors(1, "\0");
}
