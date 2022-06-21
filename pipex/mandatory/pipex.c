/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/21 15:57:57 by hbecki           ###   ########.fr       */
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

void	ft_errors(int code)
{
	ft_putnbr_fd(code, 2);
	write(2, "  got in error function\n", 24);
	ft_putstr_fd(strerror(errno), 2);
	// exit(code);
}

void	ft_check_malloc(void *data)
{
	if (data == NULL)
		ft_errors(1);
}
