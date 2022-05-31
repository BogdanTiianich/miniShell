/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:27:52 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/15 17:48:20 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*tmp_for_list;
	int		i;

	tmp = NULL;
	i = 0;
	tmp_for_list = NULL;
	while (lst != NULL)
	{
		new = ft_lstnew((*f)(lst->content));
		ft_lstadd_back(&tmp, new);
		if (new == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		tmp_for_list = lst;
		lst = lst->next;
		i++;
	}
	if (i == 1)
		tmp = new;
	return (tmp);
}
