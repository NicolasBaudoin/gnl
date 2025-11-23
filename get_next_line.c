/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:49:34 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/23 18:39:02 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_create_line_line(char *stash, int index, int len)
{
	char	*new_stash;
	char	*line;

	line = ft_substr(stash, 0, index + 1);
	new_stash = ft_substr(stash, index + 1, len - (index + 1));
	free(stash);
	stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static	char	*stash;
	char			buffer[1024];
	int				len;
	char 			*line;

	if(fd == -1)
	{
		return (NULL);
	}
	else
	printf("\nFile : opened sucessfully!\n");

	while (ft_check_and_find_eol(stash) == '0')
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break;
		buffer[len] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	if (stash)
	{
		line = ft_create_line(stash);
		stash = ft_clean(stash);
		return (line);
	}
	printf("\t%d bytes read!\n", len);
	printf("File Contents: %s\n", buffer);
	printf("Stash content: %s\n", stash);
	return (NULL);
}
