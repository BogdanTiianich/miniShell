/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:00:22 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:19 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp_list;

	tmp_list = *lst;
	if (tmp_list == NULL)
		*lst = new;
	else
	{	
		tmp_list = *lst;
		while (tmp_list->next != NULL)
		{
			tmp_list = tmp_list->next;
		}
		tmp_list->next = new;
	}
}
