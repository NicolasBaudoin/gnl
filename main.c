/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:32:10 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/23 21:29:31 by nbaudoin         ###   ########.fr       */
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
	printf("%s", get_next_line(fd));
	return (0);
}
