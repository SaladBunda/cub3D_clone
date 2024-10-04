/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:08:00 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/22 17:25:24 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*free_and_join(char *stash, char *buffer)
{
	char	*joined;

	joined = ft_strjoin_split(stash, buffer);
	free(stash);
	return (joined);
}

char	*read_and_stash(char *stash, int fd)
{
	int		br;
	char	buffer[BUFFER_SIZE + 1];

	br = 1;
	while (br > 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br == -1)
		{
			if (stash)
				free(stash);
			return (NULL);
		}
		buffer[br] = 0;
		stash = free_and_join(stash, buffer);
		if (ft_strchr_split(buffer, '\n') || stash == NULL)
			break ;
	}
	return (stash);
}

char	*process_line(char *stash)
{
	char	*newline_ptr;
	char	*line;
	int		len;

	if (!stash || !stash[0])
		return (NULL);
	newline_ptr = ft_strchr_split(stash, '\n');
	if (!newline_ptr)
		return (ft_strdup_split(stash));
	len = newline_ptr - stash;
	line = ft_substr(stash, 0, len);
	return (line);
}

char	*update_stash(char *stash)
{
	char	*newline_ptr;
	char	*new_stash;

	if (!stash)
		return (NULL);
	newline_ptr = ft_strchr_split(stash, '\n');
	if (!newline_ptr)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup_split(newline_ptr + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_and_stash(stash, fd);
	if (stash == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = process_line(stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
