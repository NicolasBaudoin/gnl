/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:49:34 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/12/18 15:38:35 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_reset_stash_buffer(char **stash, char **buffer)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*ft_extract_line_from_stash(char **stash)
{
	char	*new_stash;
	char	*line;
	int		index;

	if (!stash || !*stash)
		return (NULL);
	index = ft_check_and_find_eol(*stash);
	if (index == -1)
	{
		line = ft_subs_gnl(*stash, 0, ft_strlen(*stash));
		free(*stash);
		*stash = (NULL);
		return (line);
	}
	line = ft_subs_gnl(*stash, 0, index + 1);
	new_stash = ft_subs_gnl(*stash, index + 1, ft_strlen(*stash) - (index + 1));
	free(*stash);
	*stash = new_stash;
	return (line);
}

static int	read_loop(int fd, char **stash, char *buffer)
{
	int		bytes;
	char	*tmp;

	bytes = 1;
	while (ft_check_and_find_eol(*stash) == -1 && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin_gnl(stash, buffer);
		if (!tmp)
			return (-1);
		*stash = tmp;
	}
	return (bytes);
}

static int	read_and_stash(int fd, char **stash)
{
	char	*buffer;
	int		bytes;

	if (BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = read_loop(fd, stash, buffer);
	if (bytes == -1)
		ft_reset_stash_buffer(stash, &buffer);
	free(buffer);
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1023)
		return (NULL);
	bytes = read_and_stash(fd, &stash);
	if (bytes <= 0 || !stash || stash[0] == '\0')
	{
		ft_reset_stash_buffer(&stash, NULL);
		return (NULL);
	}
	line = ft_extract_line_from_stash(&stash);
	return (line);
}
