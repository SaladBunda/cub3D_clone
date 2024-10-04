/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:25:06 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/02 21:09:58 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, int n)
{
	int	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}


void	*ft_memcpy(void *dst, const void *src, int n)
{
	int	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}


void	*ft_memmove(void *dst, const void *src, int len)
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

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	int	len;

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



char	*ft_substr(char const *s,  int start, int len)
{
	char	*sub;
	int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
		sub[i++] = s[start++]; 
	sub[i] = '\0';
	return (sub);
}

int	ft_fcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ncount(long n)
{
	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*allocate(int *n, long *i)
{
	char	*str;

	if ((*n) < 0)
	{
		str = (char *)malloc(((*i) + 2) * sizeof(char));
		(*i)++;
	}
	else
		str = (char *)malloc(((*i) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

// static int	space(int c)
// {
// 	if ((c >= 9 && c <= 13) || c == 32) 
// 		return (1);
// 	else
// 		return (0);
// }

int	ft_atoi(char *s, int *error)
{
	int					i;
	int					sign;
	long long			num;

	i = 0;
	if (ft_fcmp(s, "-0") == 0 || ft_fcmp(s, "+0") == 0 || ft_fcmp(s, "0") == 0)
		return (0);
	num = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			sign = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 +(s[i++] - 48);
	}
	if (s[i] != '\0' || num == 0 || (num * sign) > 2147483647 || (num * sign) < -2147483648)
		*error = 1;
	return (num * sign);
}

char	*ft_itoa(int n)
{
	long	i;
	long	cpy;
	char	*str;

	cpy = n;
	if (n < 0)
		cpy = (long)n * (-1);
	i = ncount(cpy);
	str = allocate(&n, &i);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	str[i] = '\0';
	while (cpy > 0)
	{
		str[i-- - 1] = (cpy % 10) + 48;
		cpy /= 10; 
	}
	return (str);
}