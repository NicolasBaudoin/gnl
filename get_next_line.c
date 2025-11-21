/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:49:34 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/21 15:23:05 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
char	*get_next_line(int fd)
{
	static	char	*stash;
	char			buffer[1024];
	int				bytesRead;
	int i = 0;

	if(fd == -1)
	{
		return (NULL);
	}
	else
		printf("\nFile : opened sucessfully!\n");
	bytesRead = read(fd, buffer, BUFFER_SIZE);

	printf("\t%d bytes read!\n", bytesRead);
	printf("File Contents: %s\n", buffer);
	return (stash);
}