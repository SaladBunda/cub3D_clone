/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:12:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/25 12:23:31 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libr.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len)
		{
			len--;
			*(unsigned char *)(len + dst) = *(unsigned char *)(len + src);
		}
	}
	return (dst);
}
