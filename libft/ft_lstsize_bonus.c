/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:08 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:26:42 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *list)
{
	t_list	*tmp_list;
	int		i;

	i = 0;
	tmp_list = list;
	while (tmp_list != NULL)
	{
		i++;
		tmp_list = tmp_list->next;
	}
	return (i);
}
