/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:39:44 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/21 20:11:13 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_uns_name(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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

	if (ft_strchr(arg, '=') == NULL)
		return (NULL);
	if (arg[0] == '=')
	{
		ft_errors(123);
		return (NULL);
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
		ft_errors(1);
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

void	ft_env(t_info *info)
{
	ft_print_lists(info->envp_list, NULL);
}

t_lists	*ft_create_list_elem(char *key, char *value)
{
	t_lists	*elem;

	if (!key || !value)
		return (NULL);
	elem = (t_lists *)malloc(sizeof(t_lists));
	ft_check_malloc(elem);
	elem->key = key;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

t_lists	*ft_export(t_lists *env, char **elems)
{
	t_lists	*tmp_elems;
	t_lists	*tmp_env;
	t_lists	*prev_elem_env;
	t_lists	*tmp_for_next;
	t_lists	*tmp;
	int		diff;
	int		place_found_flag;
	int		match_flag;
	int		i;
	char	**key_value;

	i = 0;
	while (elems[i] != NULL)
	{
		key_value = ft_exp_uns_parser(elems[i]);
		if (key_value == NULL)
		{
			i++;
			continue ;
		}
		if (ft_exp_uns_name(key_value[0]) == 1)
		{
			ft_errors(5454);
			i++;
			continue ;
		}
			
		if (key_value[1] == NULL)
			key_value[1] = ft_create_str("");
		// ft_split_print(key_value);
		// exit(1);
		tmp_env = env;
		prev_elem_env = NULL;
		match_flag = 0;
		place_found_flag = 0;
		while (tmp_env != NULL)
		{
			diff = ft_strncmp(key_value[0], tmp_env->key, \
			ft_strlen(key_value[0]));
			if (diff == 0 && ft_strlen(key_value[0]) == ft_strlen(tmp_env->key))
			{
				// printf("MATCH\n");
				match_flag = 1;
				free(tmp_env->value);
				tmp_env->value = ft_create_str(key_value[1]);
				break ;
			}
			if (diff < 0)
				place_found_flag = 1;
			if (place_found_flag == 0)
				prev_elem_env = tmp_env;
			tmp_env = tmp_env->next;
		}
		if (match_flag == 0)
		{
			if (prev_elem_env != NULL)
			{
				// printf("ADD\n");
				tmp_for_next = prev_elem_env->next;
				tmp = ft_create_list_elem(key_value[0], key_value[1]);
				prev_elem_env->next = tmp;
				tmp->next = tmp_for_next;
			}
			else
			{
				// printf("ADD at TOP\n");
				tmp = ft_create_list_elem(key_value[0], key_value[1]);
				env = add_to_top(env, tmp, 4);
			}
		}
		i++;
	}
	return (env);
}

int	ft_check_if_builtins(t_process_config *process, t_info *info)
{
	char	**command;

	
	if (ft_strncmp(process->command->command, PWD, ft_strlen(PWD)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		ft_pwd(1);
		return (1);
	}
	if (ft_strncmp(process->command->command, ENV, ft_strlen(ENV)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		ft_env(info);
		return (1);
	}
	if (ft_strncmp(process->command->command, EXPORT, ft_strlen(EXPORT)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		command = ft_get_array(process->command);
		command++;
		info->envp_list = ft_export(info->envp_list, \
		command);
		ft_env(info);
		return (1);
	}
	if (ft_strncmp(process->command->command, UNSET, ft_strlen(UNSET)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		command = ft_get_array(process->command);
		command++;
		info->envp_list = ft_unset(info->envp_list, \
		command);
		return (1);
	}
	if (ft_strncmp(process->command->command, CD, ft_strlen(CD)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		info->envp_list = ft_cd(ft_get_array(process->command)[1], \
		&(info->envp_list));
		return (1);
	}
	if (ft_strncmp(process->command->command, ECHO, ft_strlen(ECHO)) == 0)
	{
		ft_heredoc_handler(process);
		ft_handle_write_stuff(process);
		command = ft_get_array(process->command);
		command++;
		ft_echo(command);
		return (1);
	}
	return (0);
}

t_lists	*ft_unlink_elem_from_list(t_lists *list, char *unset, int free_flag)
{
	t_lists	*tmp;
	t_lists	*prev_elem_env;
	int		len_unset;

	tmp = list;
	prev_elem_env = NULL;
	len_unset = ft_strlen(unset);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, unset, len_unset) == 0)
		{
			prev_elem_env->next = tmp->next;
			if (free_flag)
				free(tmp);////фришить нужно и внутренности
			break ;
		}
		prev_elem_env = tmp;
		tmp = tmp->next;
	}
	return (list);
}

t_lists	*ft_unset(t_lists *list, char **unset)
{
	int	i;

	i = 0;
	while (unset[i] != NULL)
	{
		if (ft_exp_uns_name(unset[i]) == 1)
			ft_errors(5454);
		else
			list = ft_unlink_elem_from_list(list, unset[i], 1);
		i++;
	}
	return (list);
}

int	ft_check_n_arg_echo(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0' || i == 1)
		return (0);
	return (1);
}

void	ft_echo(char **arr)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	if (arr[0] != NULL)
	{
		if (ft_check_n_arg_echo(arr[0]) == 1)
		{
			n_flag = 1;
			arr++;
		}
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
	if (!n_flag)
		write(1, "\n", 1);
}

t_lists	*ft_cd(char *path, t_lists **env)
{
	char	*old_pwd;
	char	*current_pwd;
	char	**tmp;

	old_pwd = ft_pwd(0);
	if (path == NULL)
		path = ft_get_val_by_key(*env, "HOME\0");
	if (path == NULL)
		ft_errors(112);
	// ft_errors("HOME not set\0");
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		free(old_pwd);
		return (*env);
	}
	current_pwd = ft_pwd(0);
	tmp = (char **)malloc(sizeof(char *) * 2);
	ft_check_malloc(tmp);
	tmp[1] = NULL;
	tmp[0] = ft_strjoin("OLDPWD=", old_pwd);
	*env = ft_export(*env, tmp);
	free(old_pwd);
	tmp[0] = ft_strjoin("PWD=", current_pwd);
	*env = ft_export(*env, tmp);
	free(current_pwd);
	free(tmp);
	return (*env);
}
