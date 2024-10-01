/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:30:16 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/25 12:14:20 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libr.h"

static int	byte_comparison(unsigned char c1, unsigned char c2)
{
	return (c1 - c2);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				cmp;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		cmp = byte_comparison(*s1_ptr++, *s2_ptr++);
		if (cmp)
			return (cmp);
		i++;
	}
	return (0);
}
