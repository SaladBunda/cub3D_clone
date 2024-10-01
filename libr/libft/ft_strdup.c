/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:46:13 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/25 12:13:30 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libr.h"

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	len;

	len = ft_strlen(s1);
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (len == 0)
	{
		ft_bzero(buffer, 1);
		return (buffer);
	}
	ft_memmove(buffer, s1, len + 1);
	return (buffer);
}
