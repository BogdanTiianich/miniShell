/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:00:22 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lists **lst, t_lists *new)
{
	t_lists	*tmp_list;

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
