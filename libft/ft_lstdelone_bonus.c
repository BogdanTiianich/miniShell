/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:23:06 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_lists *lst, void (*del)(void *))
{
	t_lists	*next;

	if (lst)
	{
		if (del)
			del(lst->content);
		next = lst->next;
		free(lst);
		lst = next;
	}
	return ;
}
