/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:53:59 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/24 15:07:45 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lists	*ft_lstnew(void *content)
{
	t_lists	*new;

	new = (t_lists *)malloc(sizeof(t_lists));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->content = content;
	return (new);
}
