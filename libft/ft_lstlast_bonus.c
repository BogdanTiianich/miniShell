/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:52:20 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:33 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp_l;

	tmp_l = lst;
	if (lst == NULL)
		return (0);
	while (tmp_l->next != NULL)
	{
		tmp_l = tmp_l->next;
	}
	return (tmp_l);
}
