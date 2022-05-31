/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:14:28 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/18 20:34:00 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp_list;

	tmp_list = lst;
	while (tmp_list != NULL)
	{
		if (f != NULL)
			(*f)(tmp_list->content);
		tmp_list = tmp_list->next;
	}
}
