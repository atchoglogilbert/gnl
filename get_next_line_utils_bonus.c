/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:28:48 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 08:32:20 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strchri(const char *haystack, const char needle)
{
	size_t	i;

	if (haystack == NULL)
		return (0);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			break ;
		i++;
	}
	return (i);
}

char	*ft_memdup(const char *s, size_t a, size_t b)
{
	char	*ptr;
	int		i;

	if (s == NULL || b - a <= 0)
		return (NULL);
	ptr = (char *) malloc ((b - a + 1) * sizeof (char));
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (a < b)
	{
		ptr[++i] = s[a];
		a++;
	}
	ptr[++i] = '\0';
	return (ptr);
}

int	ft_strcmp(const char *s, const char *s2)
{
	size_t	i;

	i = 0;
	if (s == NULL || s2 == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] - s2[i] != 0)
			return (s[i] - s2[i]);
		i++;
	}
	return (0);
}

t_args	*ft_init(int fd, int count)
{
	t_args	*args;

	args = (t_args *) malloc (sizeof (t_args));
	if (args == NULL)
		return (NULL);
	args->fd = fd;
	args->count = count;
	return (args);
}
