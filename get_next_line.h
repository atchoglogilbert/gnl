/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:26:59 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 08:32:34 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# define MAX_FD 1024

typedef struct s_args
{
	int	fd;
	int	count;
}	t_args;
char	*get_next_line(int fd);
size_t	ft_gnl_strlen(const char *s);
size_t	ft_strchri(const char *haystack, char needle);
char	*ft_memdup(const char *s, size_t a, size_t b);
int		ft_strcmp(const char *s, const char *s2);
t_args	*ft_init(int fd, int count);
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#endif