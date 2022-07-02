/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:09:00 by bogdantiyan       #+#    #+#             */
/*   Updated: 2022/07/02 12:20:46 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_part(char **arr)
{
	int	i;

	while (*arr != NULL)
	{
		i = 0;
		while ((*arr)[i] != '\0')
		{
			write(1, &(*arr)[i], 1);
			i++;
		}
		arr++;
		if (*arr != NULL)
			write(1, " ", 1);
	}
}

void	ft_echo(char **arr)
{
	int	n_flag;

	n_flag = 0;
	if (arr[0] != NULL)
	{
		if (ft_check_n_arg_echo(arr[0]) == 1)
		{
			n_flag = 1;
			arr++;
		}
		ft_echo_part(arr);
	}
	if (!n_flag)
		write(1, "\n", 1);
}

void	ft_exit(char **arr)
{
	if (arr[1] != NULL)
	{
		if (ft_check_exit_arg(arr) == 1)
			return ;
		exit(ft_atoi(arr[0]));
	}
	exit (0);
}

void	ft_cd_part(char **old_pwd, char **current_pwd, char ***tmp)
{
	free(*old_pwd);
	free(*current_pwd);
	free(*tmp);
}

t_lists	*ft_cd(char *path, t_lists **env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	**tmp;

	if (path == NULL)
		path = ft_get_val_by_key(*env, "HOME\0");
	if (path == NULL)
		ft_errors(1, "\0");
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (*env);
	}
	old_pwd = ft_pwd(0);
	current_pwd = ft_pwd(0);
	tmp = (char **)malloc(sizeof(char *) * 2);
	ft_check_malloc(tmp);
	tmp[1] = NULL;
	tmp[0] = ft_strjoin("OLDPWD=", old_pwd);
	*env = ft_export(*env, tmp);
	tmp[0] = ft_strjoin("PWD=", current_pwd);
	*env = ft_export(*env, tmp);
	ft_cd_part(&old_pwd, &current_pwd, &tmp);
	return (*env);
}
