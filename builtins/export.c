/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:29:10 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/01 16:04:53 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_error(void)
{
	printf("an error occured");
	exit(1);
}

t_env	*ft_create_list_elem(char *key, char *value)
{
	t_env	*elem;
	int		i;

	if (!key || !value)
		return (NULL);
	elem = (t_env *)malloc(sizeof(t_env));
	elem->key = (char *)malloc(sizeof(char) * (ft_strlen(key) + 1));
	elem->value = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
	i = 0;
	ft_strlcpy(elem->key, key, ft_strlen(key));
	ft_strlcpy(elem->value, value, ft_strlen(value));
	//check_malloc
	elem->next = NULL;
	return (elem);
}

t_env	*add_to_end(t_env *list,t_env *elem)
{
	t_env	*tmp;

	if (!list || !elem)
		return (NULL);
	tmp = list;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = elem;
	return (list);
}

t_env	*ft_unlink_elem_from_list(t_env *list, char *unset, int free_flag)
{
	t_env	*tmp;
	t_env	*prev_elem_env;
	int		len_unset;

	tmp = list;
	prev_elem_env = NULL;
	len_unset = ft_strlen(unset);
	while(tmp != NULL)
	{
		if (ft_strncmp(tmp->key, unset, len_unset) == 0)
		{
			prev_elem_env->next = tmp->next;
			if (free_flag)
				free(tmp);
			break;
		}
		prev_elem_env = tmp;
		tmp = tmp->next;
	}
	return (list);
}

void	ft_print_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

t_env	*add_to_top(t_env *list,t_env *elem)
{
	t_env	*tmp;

	if (!list || !elem)
		return (NULL);
	tmp = list;
	elem->next = list;
	list = elem;
	return (list);
}
void	ft_print_env(t_env *list, char *elem_needed)
{
	t_env	*elem1;
	int		elem_len;

	elem1 = list;
	elem_len = 0;
	if (elem_needed != NULL)
		elem_len = ft_strlen(elem_needed);
	while(elem1!= NULL)
	{
		if (elem_needed == NULL)
			printf("%s  %s\n", elem1->key,  elem1->value);
		else
		{
			if (ft_strncmp(elem1->key, elem_needed, elem_len) == 0)
			{
				printf("%s\n", elem1->value);
				break;				
			}
		}
		elem1 = elem1->next;
	}
}
void	ft_env(t_env *list)
{
	ft_print_env(list, NULL);
}

char	*ft_pwd(int	print_flag)
{
	char	*dir;

	dir = (char *)malloc(sizeof(char) * MAXDIR);
	if (getcwd(dir, MAXDIR) == NULL)
		ft_error();
	if (print_flag == 1)
		printf("%s\n", dir);
	return (dir);
}

char	*ft_create_str(char *str)
{
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(tmp, str, len);
	return (tmp);
}
t_env	*ft_export(t_env *env, t_env *elems)
{
	t_env	*tmp_elems;
	t_env	*tmp_env;
	t_env	*prev_elem_env;
	t_env	*tmp_for_next;
	t_env	*tmp;
	int		diff;
	int		place_found_flag;
	int		match_flag;

	tmp_elems = elems;	
	while (tmp_elems != NULL)
	{
		tmp_env = env;
		prev_elem_env = NULL;
		match_flag = 0;
		place_found_flag = 0;
		while (tmp_env != NULL)
		{
			diff = ft_strncmp(tmp_elems->key, tmp_env->key, ft_strlen(tmp_elems->key));
			if (diff == 0)
			{
				match_flag = 1;
				free(tmp_env->value);
				tmp_env->value = ft_create_str(tmp_elems->value);
				break;
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
				tmp_for_next = prev_elem_env->next;
				tmp = ft_create_list_elem(tmp_elems->key, tmp_elems->value);
				prev_elem_env->next = tmp;
				tmp->next = tmp_for_next;
			}
			else
			{
				tmp = ft_create_list_elem(tmp_elems->key, tmp_elems->value);
				env = add_to_top(env, tmp);
			}
		}
		tmp_elems = tmp_elems->next;
	}
	return (env);
}

t_env	*ft_unset(t_env *list, char **unset)
{
	int	i;

	i = 0;
	while (unset[i] != NULL)
	{
		list = ft_unlink_elem_from_list(list, unset[i], 1);
		i++;
	}
	return (list);
}

void 	ft_cd(char *path, t_env **env)
{
	int 	ret_value;
	char	*old_pwd;
	char	*current_pwd;
	t_env	*tmp;

	old_pwd = ft_pwd(0);
	ret_value = chdir(path);
	if (ret_value == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		free(old_pwd);
		return ;
	}
	current_pwd = ft_pwd(0);
	tmp = ft_create_list_elem("OLDPWD", old_pwd);
	ft_export(*env, tmp);
	free(tmp);
	tmp = ft_create_list_elem("PWD", current_pwd);
	ft_export(*env, tmp);
	free(tmp);
	free(old_pwd);
	free(current_pwd);
}
void	ft_echo(char *arr, int n_flag)
{

	printf("%s", arr);
	if (n_flag == 1)
	{
		printf("\n");
	}
}

int main(int argc, char **argv, char **env)
{
	t_env	*elem1;
	t_env	*export;
	t_env	*list;
	char	**unset;
	int		i;
	char **arr;
	

	i = 0;
	while (env[i] != NULL)
	{
		arr = ft_split(env[i], '=');
		elem1 = ft_create_list_elem(arr[0], arr[1]);
		if (i != 0)
			list = add_to_end(list, elem1);
		else
			list = elem1;
		i++;
	}
	
	// elem1 = ft_create_list_elem("TOP", "Shalom");
	// export = ft_create_list_elem("JOP", "ter");
	// elem1 = add_to_end(elem1, export);
	export = ft_create_list_elem("LESS", "ter");
	// export = add_to_end(elem1, export);
	list = ft_export(list, export);
	
	unset = (char **)malloc(sizeof(char *) * 4);
	unset[0] = ft_create_str("PAGER\0");
	unset[1] = ft_create_str("LESS\0");
	unset[2] = ft_create_str("LANG\0");
	unset[3] = NULL;
	list = ft_unset(list, unset);

	ft_pwd(1);

	
	ft_cd("../../Desktop", &list);
	// ft_env(list);
	ft_echo("SALSADASD", 1);

	
	printf("1233131321231233213211231213312%d\n%s\n", argc, argv[0]);
	return (0);
}