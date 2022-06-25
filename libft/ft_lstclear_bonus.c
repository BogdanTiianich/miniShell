/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:17:57 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lists **lst, void (*del)(void *))
{
	t_lists	*tmp;
	t_lists	*next;

	tmp = *lst;
	*lst = NULL;
	while (tmp != NULL)
	{
		if (del != NULL)
			(*del)(tmp->content);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
