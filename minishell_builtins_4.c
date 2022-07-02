/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:14:57 by bogdantiyan       #+#    #+#             */
/*   Updated: 2022/07/02 12:19:53 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_with_no_args(t_lists *list)
{
	t_lists	*elem1;

	elem1 = list;
	while (elem1 != NULL)
	{
		printf("declare -x %s=%s\n", elem1->key, elem1->value);
		elem1 = elem1->next;
	}
}

int	ft_check_name_export(char **key_value, char **elems, int *i)
{
	if (ft_exp_uns_name(key_value[0]) == 1)
	{
		ft_split_free(key_value);
		ft_errors(5454, elems[*i]);
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_export_find_place(t_lists *env, t_lists **prev_elem_env, \
char **key_value, int *match_flag)
{
	int		diff;
	int		place_found_flag;
	t_lists	*tmp_env;

	place_found_flag = 0;
	tmp_env = env;
	while (tmp_env != NULL)
	{
		diff = ft_strncmp(key_value[0], tmp_env->key, \
		ft_strlen(key_value[0]));
		if (diff == 0 && ft_strlen(key_value[0]) == ft_strlen(tmp_env->key))
		{
			*match_flag = 1;
			free(tmp_env->value);
			tmp_env->value = ft_create_str(key_value[1]);
			break ;
		}
		if (diff < 0)
			place_found_flag = 1;
		if (place_found_flag == 0)
			*prev_elem_env = tmp_env;
		tmp_env = tmp_env->next;
	}
	return (0);
}

t_lists	*ft_export_place_new_el(int match_flag, t_lists \
*prev_elem_env, t_lists *env, char **key_value)
{
	t_lists	*tmp_for_next;
	t_lists	*tmp;

	if (match_flag == 0)
	{
		if (prev_elem_env != NULL)
		{
			tmp_for_next = prev_elem_env->next;
			tmp = ft_create_list_elem(key_value[0], key_value[1]);
			prev_elem_env->next = tmp;
			tmp->next = tmp_for_next;
		}
		else
		{
			tmp = ft_create_list_elem(key_value[0], key_value[1]);
			env = add_to_top(env, tmp, 4);
		}
	}
	return (env);
}

t_lists	*ft_export(t_lists *env, char **elems)
{
	t_lists	*prev_elem_env;
	int		match_flag;
	int		i;
	char	**key_value;

	i = 0;
	while (elems[i] != NULL)
	{
		key_value = ft_exp_uns_parser(elems[i]);
		if (ft_check_name_export(key_value, elems, &i))
			continue ;
		if (key_value[1] == NULL)
			key_value[1] = ft_create_str("");
		prev_elem_env = NULL;
		match_flag = 0;
		ft_export_find_place(env, &prev_elem_env, key_value, &match_flag);
		env = ft_export_place_new_el(match_flag, prev_elem_env, env, key_value);
		i++;
	}
	if (i == 0)
		ft_export_with_no_args(env);
	return (env);
}
