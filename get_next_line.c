/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:28:01 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 08:32:58 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	Adds a string buffer to the current line up to buff_lim.
	If the current line is null, a line is created and
	contains henceforth exclusively the buffer.
*/
static char	*ft_lineadd(char *line, char *buff, size_t buff_lim)
{
	char	*nline;
	size_t	i;
	size_t	j;

	if (buff == NULL || buff_lim < 1)
		return (line);
	nline = (char *) malloc ((ft_gnl_strlen (line) + buff_lim) + 1);
	if (nline == NULL)
		return (line);
	i = 0;
	if (line != NULL)
	{
		while (line[i])
		{
			nline[i] = line[i];
			i++;
		}
		free (line);
	}
	j = 0;
	while (j < buff_lim)
		nline[i++] = buff[j++];
	nline[i] = '\0';
	return (nline);
}

/*
	Adds all the rest to line if rest does not contain a newline.
	Adds before+after newline to line, stores after newline and causes
	get_next_line to exit and return line so far.
*/
static int	ft_handlerest(char **buff, char **rest, char **line)
{
	char	*temp;

	if (ft_strchri (*rest, '\n') < ft_gnl_strlen (*rest))
	{
		*line = ft_lineadd (NULL, *rest, ft_strchri (*rest, '\n') + 1);
		temp = ft_memdup (*rest, ft_strchri (*rest, '\n') + 1,
				ft_gnl_strlen (*rest));
		free (*rest);
		*rest = temp;
		temp = NULL;
		if (*buff != NULL)
			*rest = ft_lineadd (*rest, *buff, ft_gnl_strlen (*buff));
		free (*buff);
		*buff = NULL;
		return (1);
	}
	else
	{
		if (ft_strcmp (*rest, "") != 0)
			*line = ft_lineadd (NULL, *rest, ft_gnl_strlen (*rest));
		free (*rest);
		*rest = NULL;
	}
	return (0);
}

/*
	Checks whether a file descriptor is valid or not.
	Returns 1 if fd is valid, 0 otherwise.
*/
static int	ft_isvalidfd(int fd, char *buff, char **rest)
{
	if (fd < 0 || fd > MAX_FD || read (fd, buff, 0) == -1)
	{
		free (*rest);
		*rest = NULL;
		free (buff);
		return (0);
	}
	return (1);
}

/*
	Read buffer and add to the current line.
	If buffer contains a newline, it adds buffer before+incl newline
	to line and stops reading.
	Otherwise it adds all the buffer and continues reading until its 
	encounters a null terminator
	or read returns 0.
*/
static void	ft_read(char **line, char **buff, char **rest, t_args *args)
{
	if (args == NULL)
		return ;
	while (args->count > 0)
	{
		if (ft_strchri (*buff, '\n') == ft_gnl_strlen (*buff))
		{
			*line = ft_lineadd(*line, *buff, ft_gnl_strlen (*buff));
			args->count = read (args->fd, *buff, BUFFER_SIZE);
			(*buff)[args->count] = '\0';
		}
		else
		{
			*line = ft_lineadd(*line, *buff, ft_strchri (*buff, '\n') + 1);
			*rest = ft_memdup (*buff, ft_strchri (*buff, '\n') + 1,
					ft_gnl_strlen (*buff));
			free (args);
			return ;
		}
	}
	free (args);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	size_t		count;
	static char	*rest;

	buff = (char *) malloc (BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	if (!ft_isvalidfd (fd, buff, &rest))
		return (NULL);
	line = NULL;
	count = read (fd, buff, BUFFER_SIZE);
	buff[count] = '\0';
	if (rest != NULL)
		if (ft_handlerest (&buff, &rest, &line))
			return (line);
	ft_read (&line, &buff, &rest, ft_init (fd, count));
	free (buff);
	return (line);
}
