/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 20:09:32 by hbecki            #+#    #+#             */
/*   Updated: 2021/10/16 18:27:06 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void static	ft_putnbr_fd_helper(int n, int i, int fd)
{
	char	c;

	if ((n / 10) * i > 0)
	{
		ft_putnbr_fd_helper(n / 10, i, fd);
	}
	if ((i == -1) && !((n / 10) * i > 0))
	{
		c = '-';
		write(fd, &c, 1);
	}
	c = (n % 10) * i + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 1;
	if (n < 0)
		i = -1;
	ft_putnbr_fd_helper(n, i, fd);
}
