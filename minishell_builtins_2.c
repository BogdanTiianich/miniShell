/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:14:57 by bogdantiyan       #+#    #+#             */
/*   Updated: 2022/07/02 10:15:29 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_uns_name(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (ft_isdigit(arg[0]))
		return (1);
	while (arg[i] != '\0')
	{
		if (!(ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_'))
			return (1);
		if (ft_isdigit(arg[i]))
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

char	**ft_exp_uns_parser(char *arg)
{
	char	**res;

	if (ft_strchr(arg, '=') == NULL || ft_strlen(arg) <= 1)
	{
		res = (char **)malloc(sizeof(char *) * 2);
		ft_check_malloc(res);
		res[0] = ft_create_str(arg);
		res[1] = NULL;
		return (res);
	}
	res = ft_split(arg, '=');
	ft_check_malloc(res);
	return (res);
}

char	*ft_pwd(int print_flag)
{
	char	*dir;

	dir = (char *)malloc(sizeof(char) * MAXDIR);
	if (getcwd(dir, MAXDIR) == NULL)
		ft_errors(1, "\0");
	if (print_flag == 1)
		ft_putstr_fd(dir, 1);
	return (dir);
}

void	ft_print_lists(t_lists *list, char *elem_needed)
{
	t_lists	*elem1;
	int		elem_len;

	elem1 = list;
	elem_len = 0;
	if (elem_needed != NULL)
		elem_len = ft_strlen(elem_needed);
	while (elem1 != NULL)
	{
		if (elem_needed == NULL)
			printf("%s=%s\n", elem1->key, elem1->value);
		else
		{
			if (ft_strncmp(elem1->key, elem_needed, elem_len) == 0)
			{
				printf("%s\n", elem1->value);
				break ;
			}
		}
		elem1 = elem1->next;
	}
}

void	*ft_get_val_by_key(t_lists *list, char *key_needed)
{
	t_lists	*tmp;
	int		elem_len;

	tmp = list;
	elem_len = 0;
	if (key_needed != NULL)
		elem_len = ft_strlen(key_needed);
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key_needed, elem_len) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
