/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:32:10 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/25 16:14:55 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	char	*file_name;
	int		fd;
	file_name = "test.txt";
	fd = open(file_name, O_RDWR);
	char *result = get_next_line(fd);
	while (result != NULL)
	{
		printf("%s", result);
		free(result);
		result = get_next_line(fd);
	}
	printf("%s", result);
	free(result);
	close(fd);
	return (0);
}
