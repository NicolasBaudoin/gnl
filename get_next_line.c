/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:49:34 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/12/18 02:02:46 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_size_malloc(void)
{
	if (BUFFER_SIZE <= 0)
		return (0);
	return (BUFFER_SIZE + 1);
}

char	*ft_extract_line_from_stash(char **stash)
{
	char	*new_stash;
	char	*line;
	int		index;

	if (!*stash)
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(ft_size_malloc());
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (ft_check_and_find_eol(stash) == -1 && bytes > 0)
	{
		buffer[bytes] = '\0';
		stash = ft_strjoin_gnl(&stash, buffer);
	}
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		free(buffer);
		return (NULL);
	}
	line = ft_extract_line_from_stash(&stash);
	free(buffer);
	return (line);
}
