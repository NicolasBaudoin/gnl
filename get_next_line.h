/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:47:23 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/12/14 17:16:30 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
int		ft_check_and_find_eol(char *stash);
char	*ft_extract_line_from_stash(char **stash);
char	*ft_subs_gnl(char *s, int start, int len);
char	*ft_strjoin_gnl(char **stash, char *buffer);

#endif
