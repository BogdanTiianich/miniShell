/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:32:27 by snuts             #+#    #+#             */
/*   Updated: 2021/10/27 01:02:27 by snuts            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*rem_0(char *rem)
{
	char	*line;

	line = ft_substr(rem, 0, ft_strlen(rem));
	if (ft_strlen(line) == 0)
	{
		free (line);
		line = NULL;
		return (NULL);
	}
	return (line);
}

char	*ft_line1(char **rem, int check)
{
	char	*line;

	line = ft_substr(*rem, 0, check + 1);
	*rem = rem_swap(*rem, check);
	return (line);
}

char	*ft_line2(int ret, char **rem)
{
	char	*line;

	if (!ret)
	{
		line = rem_0(*rem);
		free(*rem);
		*rem = NULL;
		return (line);
	}
	free(*rem);
	*rem = NULL;
	return (NULL);
}

void	ft_read(int fd, int *ret, char *buf, int x)
{
	*ret = read(fd, buf, x);
	buf[*ret] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*rem[1024];
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	int			check;

	check = -1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (rem[fd] == NULL)
	{
		ft_read(fd, &ret, buf, BUFFER_SIZE);
		rem[fd] = ft_substr(buf, 0, ft_strlen(buf));
	}
	while (check == -1 && ret != 0)
	{
		check = check_n(rem[fd]);
		if (check == -1 && ret != 0)
		{
			ft_read(fd, &ret, buf, BUFFER_SIZE);
			rem[fd] = ft_strjoin(rem[fd], buf);
		}
		else if (check != -1 && ret != 0)
			return (ft_line1(&rem[fd], check));
	}
	return (ft_line2(ret, &rem[fd]));
}
