/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/25 17:10:21 by hbecki           ###   ########.fr       */
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
	write(2, "  got in error function\n", 24);
	sada = ft_create_str(str);
	ft_putstr_fd(sada, 2);
	if (code == 5454)
	{
		printf("minishell: export: '%s' not a valid identifer\n", sada);
		return (1);
	}
	if (code == 123)
	{
		printf("minishell: '%s': command not found\n", sada);
		return (1);
	}
	if (code == 335)
	{
		printf("minishell: exit: %s\n", sada);
		return (1);
	}
	if (code == 336)
	{
		printf("minishell: exit: %s: numeric argument required\n", sada);
		return (1);
	}
	free(sada);
	ft_putstr_fd(strerror(errno), 2);
}

void	ft_check_malloc(void *data)
{
	if (data == NULL)
		ft_errors(1, "\0");
}
