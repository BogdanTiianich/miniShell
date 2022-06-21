/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/21 19:24:02 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	char	**ss;
	char	**s;

	ss = NULL;
	s = ft_find_word_path(envp);
	if (s == NULL)
		return (NULL);
	else
	{
		ss = ft_split(s[1], ':');
		ft_split_free(s);
		return (ss);
	}
	return (NULL);
}
