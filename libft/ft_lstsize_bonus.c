/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:50:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lists *list)
{
	t_lists	*tmp_list;
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
