/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:28:48 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 08:32:09 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*

	Get the length of a string.
	
	// Arguments:
			const char *s: the string.

	// Return: size_t length.
	
	// Return cases:
			On success: the length of the string;
			On error: 0.
			
*/	
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

/*

	Find the first position of a character in a string from its beginning.
	
	// Arguments:
			const char *haystack: the string to browse for the character;
			const char needle: the character to look for.

	// Return: size_t position.
	
	// Return cases:
			On success: the position of the character;
			On failure: the position of the null terminator;
			On error: 0.
			
*/
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

/*

	Duplicate a section of a string.
	
	// Arguments:
			const char *s: the string;
			sizet a: the start position in the string of the duplication;
			sizet b: the stop position of the duplication.

	// Return: char *substring.
	
	// Return cases:
			On success: the substring;
			On error: NULL.

*/
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

/*

	Compare a string to another string.
	
	// Arguments:
			const char *s: the string;
			const char *s2: the string to compare *s to.

	// Return: int result.
	
	// Return cases:
			On success: 0 if both strings are equal;
						a negative number if *s is smaller than *s2;
						a positive number if *s is bigger than *s2.
			On error: -1.
			
*/
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

/*

	i. Helper function, not static.

	Create a struct to hold the file descriptor and the count of
	a read function call.
	
	// Arguments:
			int fd: the file descriptor;
			int count: the count returned by read (<-<unistd.h>).

	// Return: t_args (<-"get_next_line.h") args.
	
	// Return cases:
			On success: the struct holding the arguments;
			On failure: NULL.
			
*/
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
