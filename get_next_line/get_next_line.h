/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:01:24 by snuts             #+#    #+#             */
/*   Updated: 2022/04/03 17:47:14 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

int		check_n(char *str);
int		ft_strlen_n(char *src);
char	*get_next_line(int fd);
char	*ft_strjoin_n(char *s1, char *s2);
char	*ft_strdup_n(char *src);
char	*ft_substr_n(char *s, int start, size_t len);
char	*rem_swap(char *rem, int check);

#endif
