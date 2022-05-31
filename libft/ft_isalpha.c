/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:31:02 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/18 22:29:02 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int static	ft_islower(int c)
{
	if ((c >= 97) && (c <= 122))
		return (1);
	else
		return (0);
}

int static	ft_isupper(int c)
{
	if ((c >= 65) && (c <= 90))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if (ft_islower(c) + ft_isupper(c) > 0)
		return (1);
	else
		return (0);
}
