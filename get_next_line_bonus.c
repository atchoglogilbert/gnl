/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:10:07 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 08:33:11 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int	ft_handlerest(char **buff, char **rests, char **line, int fd)
{
	char	*temp;

	if (ft_strchri (rests[fd], '\n') < ft_gnl_strlen (rests[fd]))
	{
		*line = ft_lineadd (NULL, rests[fd], ft_strchri (rests[fd], '\n') + 1);
		temp = ft_memdup (rests[fd], ft_strchri (rests[fd], '\n') + 1,
				ft_gnl_strlen (rests[fd]));
		free (rests[fd]);
		rests[fd] = temp;
		temp = NULL;
		if (*buff != NULL)
			rests[fd] = ft_lineadd (rests[fd], *buff, ft_gnl_strlen (*buff));
		free (*buff);
		*buff = NULL;
		return (1);
	}
	else
	{
		if (ft_strcmp (rests[fd], "") != 0)
			*line = ft_lineadd (NULL, rests[fd], ft_gnl_strlen (rests[fd]));
		free (rests[fd]);
		rests[fd] = NULL;
	}
	return (0);
}

static int	ft_isvalidfd(int fd, char *buff, char **rests)
{
	if (fd < 0 || fd > MAX_FD || read (fd, buff, 0) == -1)
	{
		if (fd > 0)
		{
			free (rests[fd]);
			rests[fd] = NULL;
		}
		free (buff);
		return (0);
	}
	return (1);
}

static void	ft_read(char **line, char **buff, char **rests, t_args *args)
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
			rests[args->fd] = ft_memdup (*buff, ft_strchri (*buff, '\n') + 1,
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
	static char	*rests[MAX_FD];

	buff = (char *) malloc (BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	if (!ft_isvalidfd (fd, buff, rests))
		return (NULL);
	line = NULL;
	count = read (fd, buff, BUFFER_SIZE);
	buff[count] = '\0';
	if (rests[fd] != NULL)
		if (ft_handlerest (&buff, rests, &line, fd))
			return (line);
	ft_read (&line, &buff, rests, ft_init (fd, count));
	free (buff);
	return (line);
}
