/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:49:34 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/20 17:32:45 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static	count;

	if(fd == -1){
		write(2, "NULL", 5);
		return (NULL);
	}
	else{
		printf("\nFile : opened sucessfully!\n");
	}


	char buffer[1024];

	int bytesRead = read(fd, buffer, ft_strlen(buffer));

	printf("\t%d bytes read!\n", bytesRead);
	printf("File Contents: %s\n", buffer);

	return (buffer);
}