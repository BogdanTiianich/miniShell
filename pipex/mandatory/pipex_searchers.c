/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_searchers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/02 12:21:43 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path_new(char **env)
{
	int		i;
	char	**ans;
	char	**paths;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	ans = ft_split(env[i], '=');
	if (ans == NULL)
		return (NULL);
	paths = ft_split(ans[1], ':');
	ft_split_free(ans);
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	**ft_get_array_com(t_commands *list)
{
	t_commands	*tmp;
	int			count;
	char		**arr;

	tmp = list;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	ft_check_malloc(arr);
	tmp = list;
	count = 0;
	while (tmp)
	{
		arr[count] = tmp->command;
		tmp = tmp->next;
		count++;
	}
	arr[count] = NULL;
	return (arr);
}

char	**ft_get_array_list(t_lists *list)
{
	t_lists		*tmp;
	int			count;
	char		**arr;

	tmp = list;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	ft_check_malloc(arr);
	tmp = list;
	count = 0;
	while (tmp)
	{
		arr[count] = ft_strjoin(tmp->key, tmp->value);
		tmp = tmp->next;
		count++;
	}
	arr[count] = NULL;
	return (arr);
}

char	*ft_check_access_new(char *cmd, char **paths)
{
	int		i;
	char	*s;
	char	*tmp;

	if (paths == NULL)
		return (NULL);
	if (access(cmd, 1) == -1)
	{
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			ft_check_malloc(tmp);
			s = ft_strjoin(tmp, cmd);
			ft_check_malloc(s);
			free(tmp);
			if (access(s, 1) != -1)
				return (s);
			free(s);
			i++;
		}
	}
	return (NULL);
}
