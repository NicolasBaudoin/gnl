/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaudoin <nbaudoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:20:45 by nbaudoin          #+#    #+#             */
/*   Updated: 2025/11/23 21:28:23 by nbaudoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_check_and_find_eol(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (-1);
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char  *s, int start, int len)
{
	int		i;
	char	*p;
	int		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
char	*ft_strjoin(char **stash, char *buffer)
{
	char	*new;
	int		i;
	int		k;

	if (!buffer)
		return  ;
	if (!*stash)
	{
		*stash = malloc(1);
		if (!*stash)
			return (NULL);
		(*stash)[0] = '\0';
	}
	new = malloc(ft_strlen(*stash) + ft_strlen(buffer) + 1);
	if (!new)
		return (NULL);
	i = -1;
	while ((*stash)[++i])
		new[i] = (*stash)[i];
	k = -1;
	while (buffer[++k])
		new[i + k] = buffer[k];
	new[i + k] = '\0';
	free(*stash);
	return (new);
}

